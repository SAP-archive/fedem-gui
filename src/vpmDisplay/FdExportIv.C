// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

///////////////////
//
//        This code was written by
//  Morten Eriksen from Norsk Simulator Senter
//           02.Jan.1997
//
/////////////////

#include <Inventor/actions/SoWriteAction.h>
#include <Inventor/actions/SoSearchAction.h>
#include <Inventor/nodekits/SoBaseKit.h>
#include <Inventor/nodes/SoGroup.h>
#include <Inventor/nodes/SoSwitch.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoPolygonOffset.h>
#include <Inventor/nodekits/SoNodeKitListPart.h>

#include "vpmDisplay/FdExportIv.H"


// Struct to hold information we need about top nodes in the node kits.
struct topnode {
  int index, rightSibling;
  SoNode* childptr;
  topnode* next;
};

// Convert an SoNodeKitListPart to an SoGroup. NB!! If any other
// SoGroup-derived nodes than SoSwitch and SoSeparator are used as
// catalog nodes, this function must be expanded to handle the new
// node types.
static SoGroup* kitlistToSubgraph(SoNodeKitListPart* list)
{
  SoType listtype = list->getContainerType();

  SoGroup *group;

  if(listtype == SoSwitch::getClassTypeId()) {
    SoSwitch* swnode = new SoSwitch;
    swnode->whichChild.setValue(SO_SWITCH_ALL);
    group = swnode;
  }
  else if(listtype == SoSeparator::getClassTypeId())
    group = new SoSeparator;
  else if(listtype == SoGroup::getClassTypeId())
    group = new SoGroup;
  else
    return NULL;

  // Get children.
  group->setName(SbName(list->getContainerType().getName().getString()));
  for (int i = 0; i < list->getNumChildren(); i++)
    if(listtype == SoSwitch::getClassTypeId()) {
      // If the container is a switch node, we need to find out which
      // nodes are currently visible. Hack!!
      SoSearchAction search;
      search.setSearchingAll(FALSE);
      search.setNode(list->getChild(i));
      search.apply(list);
      SoFullPath *path = (SoFullPath *)search.getPath();
      if(path) group->addChild(list->getChild(i));
      search.reset();
    }
    else
      group->addChild(list->getChild(i));

  return group;
}

// Return the catalog index number for the top node parent of the given entry.
static int getTopIndex(const SoNodekitCatalog* catalog, int entry)
{
  while (catalog->getParentPartNumber(catalog->getParentPartNumber(entry)) != -1)
    entry = catalog->getParentPartNumber(entry);

  return entry;
}

// Check if the given catalog index for a top parent node has already been
// inserted in the list.
static topnode* findNode(topnode* head, int index)
{
  for (; head; head = head->next)
    if (head->index == index)
      return head;

  return NULL;
}

// Find the left neighbour of a top parent node in the list.
static topnode* findNeighbour(topnode* head, int sibling)
{
  for (; head; head = head->next)
    if (head->rightSibling == sibling)
      return head;

  return NULL;
}

#ifdef FD_DEBUG
// Show some debugging information for a catalog entry.
static void catalogInfo(SoBaseKit* kit, const SoNodekitCatalog* catalog, int entry)
{
  int parent = catalog->getParentPartNumber(entry);
  int sibling = catalog->getRightSiblingPartNumber(entry);
  SoNode* ptr = kit->getPart(catalog->getName(entry), FALSE);

  fprintf(stdout, "\nEntry %d:\n\tname: %s\n\ttype: %s\n"
	  "\tisLeaf: %d\n\tparent: %d %s\n"
	  "\trightsibling: %d %s\n\tpointer: %p\n\tpublic: %d\n",
	  entry, catalog->getName(entry).getString(),
	  catalog->getType(entry).getName().getString(),
	  catalog->isLeaf(entry),
	  parent,
	  parent == -1 ? "(none)" : catalog->getName(parent).getString(),
	  sibling,
	  sibling == -1 ? "(none)" : catalog->getName(sibling).getString(),
	  ptr, catalog->isPublic(entry));
}
#endif

// Convert any nodekit to it's respective subgraph.
static SoGroup* kitToSubgraph(SoBaseKit* kit)
{
  // Undefined pointer value
  SoNode* undef = reinterpret_cast<SoNode*>(0xffffffffull);

  // For the top node list.
  topnode* head = NULL;
  topnode* tail = NULL;
  // Debugging variables used to check that we really do get hold of
  // all the top nodes.
  int topNodes = 0, topNodesFound = 0;

  kit->setSearchingChildren(TRUE);

  // Scan the nodekit catalog and make a linked list of all the top
  // nodes we may get hold of.
  const SoNodekitCatalog *catalog = kit->getNodekitCatalog();
  int entries = catalog->getNumEntries();
  for(int i = 0; i < entries; i++) {
    // Try to get hold of the catalog entry's "real" Inventor pointer.
    SoNode *ptr = kit->getPart(catalog->getName(i), FALSE);
    // Validate top node entry.
    if(catalog->getParentPartNumber(i) == 0) {
      // If the top node is not in use, set the pointer to a def-value
      // so that we know when to insert dummy empty SoGroup nodes.
      if(!ptr && catalog->isPublic(i))
	ptr = undef;

      // If this test is TRUE, this nodekit class must be fixed if it
      // shall be possible to export it (some member(s) must be made
      // public).
      if(catalog->isLeaf(i) && !ptr && !catalog->isPublic(i)) {
	fprintf(stderr, "Warning!! Can't acquire top leaf node because it's"
		" private (in nodekit '%s').\n",
		kit->getTypeId().getName().getString());
	ptr = undef;
      }

      topNodes++;
    }

    // If ptr != NULL, this catalog entry must either be public and in
    // use, or it's a top node which is empty.
    if(ptr) {
      // Check to see if this top node is still missing in the list,
      // and if this is the case; append it.
      int index = getTopIndex(catalog,i);
      if (!findNode(head,index)) {
	topnode* newnode = new topnode;
	if(newnode) {
	  topNodesFound++;

	  newnode->index = index;
	  newnode->rightSibling = catalog->getRightSiblingPartNumber(index);
	  newnode->childptr = ptr;
	  newnode->next = NULL;
	  if(!head)
	    head = tail = newnode;
	  else {
	    tail->next = newnode;
	    tail = newnode;
	  }
	}
	else
	  fprintf(stderr, "Warning! Not enough memory.\n");
      }
    }
  }

#ifdef FD_DEBUG
  // Show debug info for all entries in the catalog.
  fprintf(stdout, "\n\nkit: '%s'\n", kit->getTypeId().getName().getString());
  for (int i = 0; i < entries; i++) catalogInfo(kit,catalog,i);
#endif

  // Some of the leaf nodes used in this nodekit are not public, which
  // makes it impossible to return the complete subgraph. The nodekit in
  // question should be fixed (some member(s) must be made public).
  if(topNodes != topNodesFound)
    fprintf(stderr, "Warning!! Could only acquire paths to %d out of %d"
	    " topnode%s. in nodekit class '%s'.\n", topNodesFound, topNodes,
	    topNodes == 1 ? "":"s", kit->getTypeId().getName().getString());

  // Group node to replace the nodekit node.
  SoGroup *replacement = new SoGroup;

  if(head) {
    // If there's at least one topnode in use, rip the guts out of the nodekit
    SoSearchAction search;
    search.setSearchingAll(TRUE);
    // Add the subtree for each top node (including the node) in sorted order
    // Hack!!
    topnode* lasthit;
    for (int ls = -1; (lasthit = findNeighbour(head,ls)); ls = lasthit->index)
      if(lasthit->childptr == undef) {
        SoGroup * dummygroup = new SoGroup;
        dummygroup->setName("dummygroup");
	replacement->insertChild(dummygroup, 0);
      }
      else {
	search.setNode(lasthit->childptr);
	search.apply(kit);
	SoFullPath *path = (SoFullPath *)search.getPath();
	replacement->insertChild(path->getNode(1), 0);
	search.reset();
      }

    // Deallocate the memory resources used in the linked top node list.
    for (topnode* runner = head; runner; runner = head) {
      head = runner->next;
      delete runner;
    }
  }

  replacement->setName(SbName(kit->getTypeId().getName().getString()));
  return replacement;
}

// Scan the graph and convert all nodekits and nodekitlistparts to
// ordinary subgraphs.
static void convertNodekits(SoNode*& root)
{
  if(root->isOfType(SoGroup::getClassTypeId())) {
    SoGroup *group = (SoGroup *)root;
    for(int j = 0; j < group->getNumChildren(); j++) {
      SoNode *child = group->getChild(j);
      if(child->isOfType(SoBaseKit::getClassTypeId())) {
	SoNode* convgraph = kitToSubgraph((SoBaseKit*)child);
	group->replaceChild(j, convgraph);
	child = group->getChild(j);
      }
      else if(child->isOfType(SoNodeKitListPart::getClassTypeId())) {
	SoNode* convgraph = kitlistToSubgraph((SoNodeKitListPart*)child);
	group->replaceChild(j, convgraph);
	child = group->getChild(j);
      }
      convertNodekits(child);
    }
  }
}

#ifdef __COIN__

// FIXME: a quick hack by pederb. For some reason morten's old
// code didn't work with Coin, and it was an ugly piece of code
// I didn't understand at all, so I just rewrote the whole thing.
// pederb@sim.no, 2001-07-31
//
#include <Inventor/misc/SoChildList.h>
#include <Inventor/lists/SoNodeList.h>
#ifdef USE_SMALLCHANGE
#include <SmallChange/nodekits/LegendKit.h>
#endif

static SoNode* copy_graph_rec(SoNode* src)
{
  SoNode* dst;
  if (src->isOfType(SoBaseKit::getClassTypeId()))
    dst = new SoGroup;
  else if (src->isOfType(SoNodeKitListPart::getClassTypeId()))
    dst = new SoGroup;
  else
    dst = src->copy(FALSE);

  SoChildList* cl = src->getChildren();
  if (!cl) return dst;

  int i;
  SoNodeList tmplist;
  for (i = 0; i < cl->getLength(); i++)
    tmplist.append((*cl)[i]);

  // empty src childlist before copying
  cl->truncate(0);

  SoChildList* dstcl = dst->getChildren();

  for (i = 0; i < tmplist.getLength(); i++) {
    // don't copy LegendKit. We use nonstandard nodes inside
    // that kit. Don't copy PolygonOffset nodes, as it's not
    // part of SGI Inventor < 2.1
    if (!tmplist[i]->isOfType(SoPolygonOffset::getClassTypeId()))
#ifdef USE_SMALLCHANGE
      if (!tmplist[i]->isOfType(LegendKit::getClassTypeId()))
#endif
	dstcl->append(copy_graph_rec(tmplist[i]));
    // restore src graph
    cl->append(tmplist[i]);
  }

  tmplist.truncate(0);
  return dst;
}
#endif // !COIN

// Exports an Inventor file to 'filename'.
bool FdExportIv::exportGraph(SoNode* root, const char* filename)
{
  if (!root) return false;

#ifdef __COIN__
  SoNode* newgraph = copy_graph_rec(root);
#else
  SoNode* newgraph = root->copy(FALSE);
  if (newgraph) convertNodekits(new_graph);
#endif

  if (newgraph) {
    newgraph->ref();
    SoOutput* out = new SoOutput;
    if (out->openFile(filename)) {
      SoWriteAction *wa = new SoWriteAction(out);
      wa->apply(newgraph);
      out->closeFile();
      newgraph->unref();
      return true;
    }
    else
      fprintf(stderr, "Couldn't write file '%s'.\n", filename);
  }

  return false;
}
