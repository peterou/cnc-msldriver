/*
 * $Id: OpponentHelper.h 1935 2007-03-19 19:50:12Z phbaer $
 *
 *
 * Copyright 2005,2006 Carpe Noctem, Distributed Systems Group,
 * University of Kassel. All right reserved.
 *
 * The code is derived from the software contributed to Carpe Noctem by
 * the Carpe Noctem Team.
 *
 * The code is licensed under the Carpe Noctem Userfriendly BSD-Based
 * License (CNUBBL). Redistribution and use in source and binary forms,
 * with or without modification, are permitted provided that the
 * conditions of the CNUBBL are met.
 *
 * You should have received a copy of the CNUBBL along with this
 * software. The license is also available on our website:
 * http://carpenoctem.das-lab.net/license.txt
 *
 *
 * <description>
 */
#ifndef OpponentHelper_H
#define OpponentHelper_H

//#include <libAnja/DatagramSocket.h>
//#include <libAnja/UnixSocket.h>
#include "../filters/FilterExtractBlobs.h"
#include "ParticleFilter.h"
#include "../global/Types.h"

#include <SystemConfig.h>

#define HEIGHT 480
#define WIDTH 640

class OpponentHelper{


	public:
		OpponentHelper();
		~OpponentHelper();

		void processOpponentBlobs(std::vector<BlobBounds> & potOpponentBlobs, Particle * maxParticle);

	protected:

		SystemConfig* sc;

		void init();
		void cleanup();

		int MX;
		int MY;

		double LocalizationSuccess;




};



#endif

