<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

# Working with the model display and model database

The mechanism database and the Open Inventor 3D visualisation are tied together
with a layer of objects whose class names have the prefix "Fd".
A `FmPart` has a `FdPart` counterpart and points to it through the pointer `itsDisplayPt`.
All model entity classes of type `FmIsRenderedBase` has this property.

The Fd-objects take care of maintaining the part of the Inventor datastructure
that is needed to visualize that object.

The Inventor datastructure is an asyclic directed graph.
That is a tree where leafs and subtrees can be used several times.
Each element in that tree is called a Node and the inventor class
`SoNode` is the base class of all nodes.

To display something using Inventor, you need an Inventor viewer,
basically the class that is the black square on the screen, and a small
scene graph that contains the geometrical information you want displayed.
The root of the scene graph is given to the viewer, and the scene graph is displayed.

Changes to the nodes in the dislayed scene graph is shown in the view instantly.

More on how Inventor is used in Fedem can be read in Jens Jacob Storen's diploma thesis.
