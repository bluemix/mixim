/* -*- mode:c++ -*- ********************************************************
 * file:        BaseWorldUtility.h
 *
 * author:      Tom Parker
 *
 * copyright:   (C) 2006 Parallel and Distributed Systems Group (PDS) at
 *              Technische Universiteit Delft, The Netherlands.
 *
 *              This program is free software; you can redistribute it
 *              and/or modify it under the terms of the GNU General Public
 *              License as published by the Free Software Foundation; either
 *              version 2 of the License, or (at your option) any later
 *              version.
 *              For further information see file COPYING
 *              in the top level directory
 ***************************************************************************
 * description: basic world utility class
 *              provides world-required values
 **************************************************************************/

#include "BaseWorldUtility.h"
#include "FindModule.h"
#include "BaseConnectionManager.h"

Define_Module(BaseWorldUtility);


const double BaseWorldUtility::speedOfLight = 299792458.0; //metres per second

BaseWorldUtility::BaseWorldUtility():
		isInitialized(false)
{}

void BaseWorldUtility::initialize(int stage) {
	if (stage == 0) {
        initializeIfNecessary();
	}
	else if(stage == 1) {
		//check if necessary modules are there
		//Connection Manager
		if(!FindModule<BaseConnectionManager*>::findGlobalModule()) {
			opp_warning("Could not find a connection manager module in the network!");
		}
	}
}

void BaseWorldUtility::initializeIfNecessary()
{
	if(isInitialized)
		return;

    playgroundSize = Coord(par("playgroundSizeX"),
                           par("playgroundSizeY"),
                           par("playgroundSizeZ"));

	if(playgroundSize.x < 0) {
		opp_error("Playground size in X direction is invalid: "\
				  "(%f). Should be greater than or equal to zero.", playgroundSize.x);
	}
	if(playgroundSize.y < 0) {
		opp_error("Playground size in Y direction is invalid: "\
				  "(%f). Should be greater than or equal to zero.", playgroundSize.y);
	}
	if(playgroundSize.z < 0) {
		opp_error("Playground size in Z direction is invalid: "\
				  "(%f). Should be greater than or equal to zero.", playgroundSize.z);
	}

	useTorusFlag = par("useTorus");

	airFrameId = 0;

	isInitialized = true;
}

Coord BaseWorldUtility::getRandomPosition()
{
	initializeIfNecessary();

    return Coord(uniform(0, playgroundSize.x),
                 uniform(0, playgroundSize.y),
                 uniform(0, playgroundSize.z));
}
