/*
 * $Id: FilterRGBToHSV.h 1531 2006-08-01 21:36:57Z phbaer $
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
#ifndef FilterRGBToHSV_H
#define FilterRGBToHSV_H

#include "Filter.h"

class FilterRGBToHSV : public Filter {


	public:
	    FilterRGBToHSV(int width, int height);
		~FilterRGBToHSV();
        
        unsigned char * segmentRgb(unsigned char * src, unsigned int imagesize);
        unsigned char * blackParts(unsigned char * src, unsigned int imagesize);

	protected:

		void init();
		void cleanup();
		void RGBtoHSV( float r, float g, float b, float *h, float *s, float *v );
		void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );
};




#endif

