<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

# Description and usage of Fedem UI-UA handlers

## The plugin concept

Plugin classes are classes that one plugs in when requesting the functionality
they introduce. To plug in a class means to inherit from it, and thereby add
its functionality into ones class. The plugin classes should not introduce a
complex inheritance hierarchy into your system, they usually are single classes.

The plugin classes are usually small library components,
with a rather limited area of functionality.
That way their usage could be quite widespread.
One often finds oneself inheriting from several plugin classes (multiple inheritance).

## The Fedem UI-UA handlers

The Fedem UI-UA handler are plugin classes that operate in pairs
with one class on the UI side and the other on the UA side.
Their responsibilities are to set up and maintain the transfer of information
between UI and UA. That transfer is callback driven since the UI code
should be independent of other code. Callback driven communication
needs a lot of setup/maintainance code, and that is the handlers tasks.
The general structure is that the UA handler has the callback functions
and the UI handler has the set/invoke methods.
The UA handler manages the communication setup.
The general usage is, after reimplementing necessary methods,
to invoke the callback function from the UI when one wants to
execute that functionality.

## The handlers

### Existence handlers

This handler pair exists mainly because Fedem book-keeps the UI instead of the UAs.
The UI must communicate with the UA and therefore the Existence handler.
The Existence handler is a remedy for a not-soo-good-design and therefore only temporary.
Its tasks is to handle the creation and destruction of this ui's UA classes.

The pair has a static factory method on the UA side
which creates the UA object on the basis of the UI pointer it gets.
This method (createUA) needs to be maintained under the implementation of new UI's.

See the class `FapUAExistenceHandler`.

### Data handlers

These pairs handle the dataflow between UI and UA. They are usually used in data dialogs,
both OK (discrete DB update) and close dialogs (continous DB update).

The following methods should be reimplemented under the usage of this pair:

* UI side : `setUIValues` (sets the values for all UI widgets)
* UA side : `createValuesObject` (creates a data carrier object)
* `setDBValues` (set values in the DB)
* `getDBValues` (set values from the DB)

See the class `FapUADataHandler`.

### Finish handlers

This pair handles the finishing process of a UI, that is making the UI disappear.

The following method should be reimplemented under the usage of this pair:

* UA side : `finishUI` (finishes the UI)

See the class `FapUAFinishHandler`.

## Example

We will take a closer look at the UI-UA pair `FuiCurveDefine`/`FapUACurveDefine`.
These classes inherit the Existence handler pair (like all UI-UA pairs) and the Data handler pair
(like all UI-UA pairs that need to transfer data between the DB objects and the UI).
This also involves the DB object itself, the class `FmCurveSet`.

When a Data handler is involved, the need for a values object arises.
This values object is always defined and implemented in the UI file, and inherits `FFuaUIValues`.
The object contains all relevant values, as public member variables.
The values object is also often called a ping-pong object,
because the values are transported back and forth between the DB and UI objects,
with the UA object as director. This behaviour is more or less
consistent with the Mediator pattern (see Design Patterns by Gamma et al).

The relationship between the three classes is as follows:
The UA object holds pointers to both the UI and the DB objects.
Neither the UI nor the DB object has any knowledge of the UA class or of each other.
This is consistent with the object oriented approach wich includes information hiding.

If you create a new UI-UA pair, be sure to give them similar names. E.g., if you want to
create a tire property panel, name the two classes `FuiTireProperties` and `FapUATireProperties`.

Upon creation of a new UI-UA pair, you must remember to register your classes in `FapUAExistenceHandler`.

### Re-implementations from base classes

The UA class re-implements these methods from `FapUADataHandler`.

* `createValuesObject` - creates the value object, and returns a pointer to it
* `getDBValues` - Fetches the values from the DB object and sets them in the values object
* `setDBValues` - Sets the values from the UI in the DB object.
  Also calls the `onChanged` method on the DB object (important!)
* `updateUIValues` - Updates the UI

The three first of these are called from the parent class, when `updateUIValues` are called.

No methods are re-implemented from the Existence handler.

The UI class re-implements these methods from `FFuUADataHandler`.

* `createValuesObject` - creates values object and returns a pointer to it
* `getUIValues` - gets values from the UI and sets them in the values object
* `setUIValues` - gets values from the values object and sets them in the UI

These methods are all called from the parent class.

No methods are re-implemented form the Existence handler.

### Qt wrapping

Since we have chosen to make wrappers around the Qt classes, the same thing must be don in the UI class.
Actually, you need to implement two classes on the UI side; `FuiYourClass` and `FuiQtYourClass`,
where `FuiQt*` inherits `Fui*`. All the necessary variables (fields, buttons, etc.)
are owned by the `Fui*` class, but are created by the `FuiQt*` class:

Example:
```
class FuiMyClass : virtual public FFuMultUIComponent,
                   public FFuUAExistenceHandler,
                   public FFuUADataHandler
{
public:
  FuiMyClass();
  virtual ~FuiMyClass();

protected:
  FFuPushButton myButton;
  FFuLabel myLabel;

protected:
  initWidgets();
...
};

class FuiQtMyClass : public FFuQtMultUIComponent,
                     public FuiMyClass
{
public:
  FuiQtMyClass(QWidget* parent, const char* name = "FuiQtMyClass");
  virtual ~FuiQtMyClass();
}
```

And then in the implementation of `FuiQtMyClass`:

```
FuiQtMyClass::FuiQtMyClass(QWidget* parent, const char* name)
  : FFuQtMultUIComponent(parent, name)
{
  this->myButton = new FFuQtPushButton(this);
  this->myField = new FFuQtField(this);

  // Base class widget initialization
  this->initWidgets();
...
}
```

### Signal handling

The UA object needs information about this that happen in the application, such as
when a DB object has changed and when the selection has changed. A convenient way of
getting this information is to subscribe to signals that are sent in the application.
To do this, an internal signal connector class is implemented.
This is a friend class of the UA class, and holds a pointer to it.
When a signal is received, such as `onModelMemberChanged` (when a DB object has changed),
the corresponding method is called in the owner UA class.

Now, remember that this signal is sent every time a DB object has changed, so it is not
necessarily a curve (which is what we are looking at now), and it is not necessarily the
"current" curve, so we need to check for that. All DB objects has a method, `getClassTypeID`,
which can be used to see if this is a DB object of "our" type.
The CurveDefine pair doesn't need to know if anything has happened to a joint.

The main thing in the `onModelMemberChanged` method is to call `updateUIValues`.

We also need to track changes to the selection state. This is most conveniently handled through
template classes specially designed for this. They will call the corresponding methods in the UA class.
The `onPermSelectionChanged` method will, if necessary, set a new pointer to its DB object,
according to the recent change in the selection state.
