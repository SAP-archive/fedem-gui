// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

/*!
  \file FapUAFinishHandler.H

  \date May 12 1999

  \brief A plugin class that is a receiver for FFuUAFinishHandler.

  \details FapUAFinishHandler's task is to handle the finishing process
  of its UI. Plugin whenever needing that fuctionallity.
  the UI and the DB. Plugin whenever needed that fuctionallity.

  \author Dag R. Christensen
*/

#ifndef FAP_UA_FINISH_HANDLER_H
#define FAP_UA_FINISH_HANDLER_H

class FFuUAFinishHandler;


class FapUAFinishHandler
{
public:
  //! The constructor sets up the FFuUAFinishHandler callback.
  FapUAFinishHandler(FFuUAFinishHandler* ui);
  virtual ~FapUAFinishHandler() {}

protected:
  //! \brief These method is used as callbacks in FFuUAFinishHandler.
  //! \details Re-implemented in inherited class to somehow put down the UI
  //! which controls the existence of the UA's.
  virtual void finishUI() = 0;
};

#endif
