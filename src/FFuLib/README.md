<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

# Wrapping of Qt

## Overview

Qt is the user interface library we are using. This library
is wrapped by our own layer of code, giving our application
a Qt-free API to access. This has been done in order to:

* Avoid dependencies of Qt into our application, to be able to
  (in some distant future) switch to some other GUI library
* To have a good place to code our own simplified access methods
  to the UI that fits our needs.

`FFuLib` is this wrapping. All the GUI components we use in Fedem
is a FFu-class. These classes are implemented by using one or more
Qt GUI components, and has a quite ... uum... not so obvious
inheritance relationships with the Qt class(es).

This API or wrapping or whatever, dictates us to implement methods
for each Qt feature we want to use in our application, and classes
for each Qt component we want to use.

This is really quite simple, and is done only once, but somtimes
we need to expand our API coverage of Qt a bit to make some feature
we want in our application.

## Implementation

The main idea behind the way the FFu classes are implemented
is that we have three inheritance branches.

One starts with `FFuComponentBase` as the base class.
Those are the classes defined as our API.

The other starts with `FFuQtComponentBase`. That is the implementation
classes of the Qt wrapping. These classes contain the implementation of
our API using Qt.

The third is the Qt inheritance relationship which starts with `QWidget`
(or actuallly `QObject`, but ...)

All those inheritance chains are inherited into the leaf FFuQt class of
each component. This FFuQt class overrides the virtual interface defined
in the corresponding FFu class. A good example on how this can end up
in a complex example is `FFuQtIconButton`.

We are depending upon a feature in C++ called multiple virtual inheritance,
which allows a class to inherit several classes which in turn inherit the
same base class. This has mostly been painless, but it means that to cast
a pointer that points to a `FFuQtIconButton` from `FFuComponentBase` to, e.g.,
`QWidget` you will need to use `dynamic_cast<QWidget*>(someFFuCompBasePtr);`.

As you see, the wrapping of Qt is done in a fairly complex way. To understand
this in detail one needs a good understanding of advanced C++ features.

However, the wrapping is fairly simple to use,
and also fairly simple to maintain and expand.
