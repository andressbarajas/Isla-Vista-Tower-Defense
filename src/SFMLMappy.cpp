/* Mappy playback library class
 * SFML 1.6 Port by Brian Glenn (Breakman79) - bglenn01@gmail.com
 * Ver 1.00 Beta (March 2010)
 *
 * Based on Allegro(R11C) and OpenGL playback libraries by
 * original Mappy creator Robin Burrows - rburrows@bigfoot.com
 *
 * Mappy Editor can be found at http://www.tilemap.co.uk/mappy.php
 */

#include <iostream>
#include <fstream>
#include "../include/SFMLMappy.h"


// Constructors
SFMLMappy::SFMLMappy(void) {
	InitMapClass();
}

SFMLMappy::SFMLMappy(const char *map_name) {
	InitMapClass();
	LoadMap(map_name);
}

SFMLMappy::SFMLMappy(const char *map_name, int x, int y, int width, int height) {
	InitMapClass();

	map_draw_x=x;
	map_draw_y=y;
	map_draw_width=width;
	map_draw_height=height;

	LoadMap(map_name);
}

// Destructor
SFMLMappy::~SFMLMappy() {
	FreeMapMem();
}

void SFMLMappy::InitMapClass() {
	int i;

	map_error				= false;
	map_is_lsb				= 0;
	map_draw_x				= 0;
	map_draw_y				= 0;
	map_draw_width			= 0;
	map_draw_height			= 0;
	map_block_str_ptr		= NULL;
	map_cmap_ptr			= NULL;
	map_anim_str_ptr		= NULL;
	map_anim_seq_ptr		= NULL;
	map_ptr					= NULL;
	map_array_ptr			= NULL;
	for (i=0; i<8; i++) {
		map_map_ptr[i]		= NULL;
		map_map_array_ptr[i] = NULL;
	}
	sfimage_ptr				= NULL;
	sfsprite_ptr			= NULL;
}


int SFMLMappy::GetMapChunkSize(const unsigned char *loc_ptr) const {
	return (((static_cast <int>(loc_ptr[0]))<<24)|((static_cast <int>(loc_ptr[1]))<<16)|((static_cast <int>(loc_ptr[2]))<<8)|(static_cast <int>(loc_ptr[3])));
}

int SFMLMappy::GetMapShort(const unsigned char *loc_ptr) const {
	int rval;

	if (map_is_lsb)
	rval = ((((int) (loc_ptr[1]))<<8)|((int) (loc_ptr[0])));
	else
	rval = ((((int) (loc_ptr[0]))<<8)|((int) (loc_ptr[1])));
	if (rval & 0x8000) rval -= 0x10000;
	return rval;
}

int SFMLMappy::GetMapLong(const unsigned char *loc_ptr) const {
	if (map_is_lsb) {
		return (((static_cast <int>(loc_ptr[3]))<<24)|((static_cast <int>(loc_ptr[2]))<<16)|((static_cast <int>(loc_ptr[1]))<<8)|(static_cast <int>(loc_ptr[0])));
	} else {
		return (((static_cast <int>(loc_ptr[0]))<<24)|((static_cast <int>(loc_ptr[1]))<<16)|((static_cast <int>(loc_ptr[2]))<<8)|(static_cast <int>(loc_ptr[3])));
	}
}

void SFMLMappy::InitMapAnims(void) const {
	ANISTR *my_an_ptr;
	if (map_anim_str_ptr==NULL) return;

	//my_an_ptr = (ANISTR *)map_anim_str_end_ptr;
	my_an_ptr = map_anim_str_end_ptr;
	my_an_ptr--;

	while (my_an_ptr->antype!=-1)
	{
		if (my_an_ptr->antype==AN_PPFR) my_an_ptr->antype = AN_PPFF;
		if (my_an_ptr->antype==AN_PPRF) my_an_ptr->antype = AN_PPRR;
		if (my_an_ptr->antype==AN_ONCES) my_an_ptr->antype = AN_ONCE;

		if ((my_an_ptr->antype==AN_LOOPR) || (my_an_ptr->antype==AN_PPRR)) {
			my_an_ptr->ancuroff = my_an_ptr->anstartoff;
			if ((my_an_ptr->anstartoff)!=(my_an_ptr->anendoff)) my_an_ptr->ancuroff=(my_an_ptr->anendoff)-1;
		} else {
			my_an_ptr->ancuroff = my_an_ptr->anstartoff;
		}
		my_an_ptr->ancount = my_an_ptr->andelay;
		my_an_ptr--;
	}
}

bool SFMLMappy::DecodeMapMPHD(unsigned char *mdat_ptr) {
	mdat_ptr += 8;
	if (mdat_ptr[0] > 1) { map_error = true; std::cerr << "Error: Map format is too new!"; return false; }
	if (mdat_ptr[2] == 1) {
		map_is_lsb = 1;
	} else {
		map_is_lsb = 0;
	}
	map_type = (int)mdat_ptr[3];
	if (map_type > 3) { map_error = true; std::cerr << "Error: Map format is too new!"; return false; }

	map_width			= (short)GetMapShort(mdat_ptr+4);
	map_height			= (short)GetMapShort(mdat_ptr+6);
	map_block_width		= (short)GetMapShort(mdat_ptr+12);
	map_block_height	= (short)GetMapShort(mdat_ptr+14);
	map_block_depth		= (short)GetMapShort(mdat_ptr+16);
	map_block_str_size	= (short)GetMapShort(mdat_ptr+18);
	map_num_block_str	= (short)GetMapShort(mdat_ptr+20);
	map_num_block_gfx	= (short)GetMapShort(mdat_ptr+22);

	if (GetMapChunkSize(mdat_ptr-4) > 28) {
		map_block_gap_x		= (int)GetMapShort(mdat_ptr+28);
		map_block_gap_y		= (int)GetMapShort(mdat_ptr+30);
		map_block_stagger_x	= (int)GetMapShort(mdat_ptr+32);
		map_block_stagger_y	= (int)GetMapShort(mdat_ptr+34);
	} else {
		map_block_gap_x		= (int)map_block_width;
		map_block_gap_y		= (int)map_block_height;
		map_block_stagger_x	= 0;
		map_block_stagger_y	= 0;
	}

	if (GetMapChunkSize (mdat_ptr-4) > 36) map_click_mask = (short) GetMapShort (mdat_ptr+36);
	else map_click_mask = 0;

	/*std::cout << "map_type: " << map_type << std::endl;
	std::cout << "map_width: " << map_width << std::endl;
	std::cout << "map_height: " << map_height << std::endl;
	std::cout << "map_block_width: " << map_block_width << std::endl;
	std::cout << "map_block_height: " << map_block_height << std::endl;
	std::cout << "map_block_depth: " << map_block_depth << std::endl;
	std::cout << "map_block_str_size: " << map_block_str_size << std::endl;
	std::cout << "map_num_block_str: " << map_num_block_str << std::endl;
	std::cout << "map_num_block_gfx: " << map_num_block_gfx << std::endl;
	std::cout << "map_block_gap_x: " << map_block_gap_x << std::endl;
	std::cout << "map_block_gap_y: " << map_block_gap_y << std::endl;
	std::cout << "map_block_stagger_x: " << map_block_stagger_x << std::endl;
	std::cout << "map_block_stagger_y: " << map_block_stagger_y << std::endl;*/

	return true;
}

bool SFMLMappy::DecodeMapCMAP(unsigned char *mdat_ptr) {
	int size;

	size = GetMapChunkSize(mdat_ptr+4);
	map_cmap_ptr = new (std::nothrow) unsigned char[size];
	if (map_cmap_ptr == 0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}
	//memcpy(map_cmap_ptr, mdat_ptr+8, size);
	std::copy(mdat_ptr+8, mdat_ptr+8+size, map_cmap_ptr);
	return true;
}

bool SFMLMappy::DecodeMapBKDT(unsigned char *mdat_ptr) {
	int i, j;
	BLKSTR *my_blkstr_ptr;

	mdat_ptr += 8;
	map_block_str_ptr = new (std::nothrow) BLKSTR[map_num_block_str];
	if (map_block_str_ptr ==0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}

	my_blkstr_ptr = map_block_str_ptr;

	j = GetMapChunkSize(mdat_ptr-4);
	i = 0; while (i < (map_num_block_str*map_block_str_size)) {
		my_blkstr_ptr->bgoff = (int)GetMapLong(mdat_ptr+i);
		my_blkstr_ptr->fgoff = (int)GetMapLong(mdat_ptr+i+4);
		my_blkstr_ptr->fgoff2 = (int)GetMapLong(mdat_ptr+i+8);
		my_blkstr_ptr->fgoff3 = (int)GetMapLong(mdat_ptr+i+12);
		if (map_type == 0) {
			my_blkstr_ptr->bgoff /= (map_block_width*map_block_height*((map_block_depth+1)/8));
			my_blkstr_ptr->fgoff /= (map_block_width*map_block_height*((map_block_depth+1)/8));
			my_blkstr_ptr->fgoff2 /= (map_block_width*map_block_height*((map_block_depth+1)/8));
			my_blkstr_ptr->fgoff3 /= (map_block_width*map_block_height*((map_block_depth+1)/8));
		}
		my_blkstr_ptr->user1 = static_cast <unsigned int>(GetMapLong(mdat_ptr+i+16));
		my_blkstr_ptr->user2 = static_cast <unsigned int>(GetMapLong(mdat_ptr+i+20));
		my_blkstr_ptr->user3 = static_cast <unsigned short int>(GetMapShort(mdat_ptr+i+24));
		my_blkstr_ptr->user4 = static_cast <unsigned short int>(GetMapShort(mdat_ptr+i+26));
		my_blkstr_ptr->user5 = mdat_ptr[i+28];
		my_blkstr_ptr->user6 = mdat_ptr[i+29];
		my_blkstr_ptr->user7 = mdat_ptr[i+30];
		if (mdat_ptr[i+31]&0x80) my_blkstr_ptr->unused3 = 1; else my_blkstr_ptr->unused3 = 0;
		if (mdat_ptr[i+31]&0x40) my_blkstr_ptr->unused2 = 1; else my_blkstr_ptr->unused2 = 0;
		if (mdat_ptr[i+31]&0x20) my_blkstr_ptr->unused1 = 1; else my_blkstr_ptr->unused1 = 0;
		if (mdat_ptr[i+31]&0x10) my_blkstr_ptr->trigger = 1; else my_blkstr_ptr->trigger = 0;
		if (mdat_ptr[i+31]&0x08) my_blkstr_ptr->br = 1; else my_blkstr_ptr->br = 0;
		if (mdat_ptr[i+31]&0x04) my_blkstr_ptr->bl = 1; else my_blkstr_ptr->bl = 0;
		if (mdat_ptr[i+31]&0x02) my_blkstr_ptr->tr = 1; else my_blkstr_ptr->tr = 0;
		if (mdat_ptr[i+31]&0x01) my_blkstr_ptr->tl = 1; else my_blkstr_ptr->tl = 0;

		i += map_block_str_size;
		my_blkstr_ptr++;
	}
	return true;
}

bool SFMLMappy::DecodeMapANDT(unsigned char *mdat_ptr) {
	int num_ani, i, an_check_size;
	unsigned char *mdat_end_ptr = NULL;

	mdat_ptr += 8;
	an_check_size = GetMapChunkSize(mdat_ptr-4);
	mdat_end_ptr = mdat_ptr+an_check_size;

	num_ani = 0;
	while (1) {
		mdat_end_ptr -= 16;
		num_ani++;
		if (*mdat_end_ptr == 255) break;
	}

	map_anim_seq_ptr = new (std::nothrow) int[(mdat_end_ptr-mdat_ptr)/4];
	if (map_anim_seq_ptr == 0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}

	i = 0;
	while (mdat_ptr != mdat_end_ptr) {
		map_anim_seq_ptr[i] = GetMapLong(mdat_ptr);
		if (map_type == 0) map_anim_seq_ptr[i] /= map_block_str_size;
		mdat_ptr += 4; i++;
	}

	map_anim_str_ptr = new (std::nothrow) ANISTR[num_ani];
	if (map_anim_str_ptr == 0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}

	map_anim_str_end_ptr = map_anim_str_ptr;
	map_anim_str_end_ptr += num_ani;

	i = 0;
	while (i<num_ani) {
		map_anim_str_ptr[i].antype = mdat_end_ptr[0];
		map_anim_str_ptr[i].andelay = mdat_end_ptr[1];
		map_anim_str_ptr[i].ancount = mdat_end_ptr[2];
		map_anim_str_ptr[i].anuser = mdat_end_ptr[3];
		if (map_type == 0) {
			map_anim_str_ptr[i].ancuroff = ((GetMapLong(mdat_end_ptr+4)+an_check_size)/4);
			map_anim_str_ptr[i].anstartoff = ((GetMapLong(mdat_end_ptr+8)+an_check_size)/4);
			map_anim_str_ptr[i].anendoff = ((GetMapLong(mdat_end_ptr+12)+an_check_size)/4);
		} else {
			map_anim_str_ptr[i].ancuroff = GetMapLong(mdat_end_ptr+4);
			map_anim_str_ptr[i].anstartoff = GetMapLong(mdat_end_ptr+8);
			map_anim_str_ptr[i].anendoff = GetMapLong(mdat_end_ptr+12);
		}
		mdat_end_ptr += 16; i++;
	}

	InitMapAnims ();
	return true;
}

bool SFMLMappy::DecodeMapBGFX(unsigned char *mdat_ptr) {
	int i, j, k, size;
	unsigned char *tgfx_ptr, *tgfx2_ptr;

	size = map_block_width*(map_block_height+2)*4;
	tgfx_ptr = new (std::nothrow) unsigned char[size];

	if (tgfx_ptr == 0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}

	std::fill_n(tgfx_ptr,size,0);

	mdat_ptr += 8;

	sfimage_ptr = new sf::Image[map_num_block_gfx];
	sfsprite_ptr = new sf::Sprite[map_num_block_gfx];

	for (i=0; i<map_num_block_gfx; i++) {
		tgfx2_ptr = tgfx_ptr+(map_block_width*4);	// 1 pix border
		for (j=0; j<map_block_height; j++) {
			for (k=0 ;k<map_block_width; k++) {
				switch (map_block_depth) {
					case 8:
						if (mdat_ptr[0] == 0) {
							tgfx2_ptr[k*4+3] = 0;
						} else {
							tgfx2_ptr[k*4+3] = 0xFF;
						}
						tgfx2_ptr[k*4] = map_cmap_ptr[mdat_ptr[0]*3];
						tgfx2_ptr[k*4+1] = map_cmap_ptr[mdat_ptr[0]*3+1];
						tgfx2_ptr[k*4+2] = map_cmap_ptr[mdat_ptr[0]*3+2];
						mdat_ptr++;
						break;
					case 15:
						tgfx2_ptr[k*4] = ((mdat_ptr[0])&0x7C)<<1;
						tgfx2_ptr[k*4+1] = ((((mdat_ptr[0])&0x3)<<3)|((mdat_ptr[1])>>5))<<3;
						tgfx2_ptr[k*4+2] = ((mdat_ptr[1])&0x1F)<<3;
						tgfx2_ptr[k*4]	|= ((tgfx2_ptr[k*4]>>5)&0x07);
						tgfx2_ptr[k*4+1] |= ((tgfx2_ptr[k*4+1]>>5)&0x07);
						tgfx2_ptr[k*4+2] |= ((tgfx2_ptr[k*4+2]>>5)&0x07);
						if (tgfx2_ptr[k*4] == MTRANSPR && tgfx2_ptr[k*4+1] == MTRANSPG &&	tgfx2_ptr[k*4+2] == MTRANSPB) {
							tgfx2_ptr[k*4+3] = 0;
						} else {
							tgfx2_ptr[k*4+3] = 0xFF;
						}
						mdat_ptr += 2;
						break;
					case 16:
						tgfx2_ptr[k*4]	= ((mdat_ptr[0])&0xF8);
						tgfx2_ptr[k*4+1] = ((((mdat_ptr[0])&0x7)<<3)|((mdat_ptr[1])>>5))<<2;
						tgfx2_ptr[k*4+2] = ((mdat_ptr[1])&0x1F)<<3;
						tgfx2_ptr[k*4] |= ((tgfx2_ptr[k*4]>>5)&0x07);
						tgfx2_ptr[k*4+1] |= ((tgfx2_ptr[k*4+1]>>6)&0x03);
						tgfx2_ptr[k*4+2] |= ((tgfx2_ptr[k*4+2]>>5)&0x07);
						if (tgfx2_ptr[k*4] == MTRANSPR && tgfx2_ptr[k*4+1] == MTRANSPG && tgfx2_ptr[k*4+2] == MTRANSPB) {
							tgfx2_ptr[k*4+3] = 0;
						} else {
							tgfx2_ptr[k*4+3] = 0xFF;
						}
						mdat_ptr += 2;
						break;
					case 24:
						tgfx2_ptr[k*4]	= mdat_ptr[0];
						tgfx2_ptr[k*4+1] = mdat_ptr[1];
						tgfx2_ptr[k*4+2] = mdat_ptr[2];
						if (tgfx2_ptr[k*4] == MTRANSPR && tgfx2_ptr[k*4+1] == MTRANSPG && tgfx2_ptr[k*4+2] == MTRANSPB) {
							tgfx2_ptr[k*4+3] = 0;
						} else {
							tgfx2_ptr[k*4+3] = 0xFF;
						}
						mdat_ptr += 3;
						break;
					case 32:
						tgfx2_ptr[k*4]	= mdat_ptr[1];
						tgfx2_ptr[k*4+1] = mdat_ptr[2];
						tgfx2_ptr[k*4+2] = mdat_ptr[3];
						tgfx2_ptr[k*4+3] = mdat_ptr[0];
						mdat_ptr += 4;
						break;
					default:
						break;
				}
				//std::cout << "[" << (int)tgfx2_ptr[k*4] << "," << (int)tgfx2_ptr[k*4+1] << "," <<  (int)tgfx2_ptr[k*4+2] << "," << (int)tgfx2_ptr[k*4+3] << "]";
			}
			//std::cout << std::endl;
			tgfx2_ptr += (map_block_width*4);
		}
		sfimage_ptr[i].LoadFromPixels(map_block_width,map_block_height,tgfx_ptr+(map_block_width*4));
		sfimage_ptr[i].SetSmooth(false);
		sfsprite_ptr[i].SetImage(sfimage_ptr[i]);
	}

	delete[] tgfx_ptr;
	return true;
}

bool SFMLMappy::DecodeMapLayer(unsigned char *mdat_ptr, int lnum) {
	int i, j, k, l;
	short int *my_map_ptr = NULL;
	short int *my_map2_ptr = NULL;

	map_map_ptr[lnum] = new (std::nothrow) short int[map_width*map_height];
	if (map_map_ptr[lnum] == 0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}

	mdat_ptr += 8;
	my_map_ptr = map_map_ptr[lnum];

	if (map_type == 0) {
	for (j=0; j<map_height; j++) {
		for (i=0; i<map_width; i++) {
			*my_map_ptr = static_cast <short int>(GetMapShort(mdat_ptr));
			if (*my_map_ptr >= 0) { *my_map_ptr /= map_block_str_size; }
			else { *my_map_ptr /= 16; }
			mdat_ptr+=2; my_map_ptr++;
		}
	}
	} else {
	if (map_type == 1) {
	for (j=0; j<map_height; j++) {
		for (i=0; i<map_width; i++) {
			*my_map_ptr = static_cast <short int>(GetMapShort(mdat_ptr));
			mdat_ptr+=2; my_map_ptr++;
		}
	}
	} else {
	if (map_type == 2) {
	for (j=0; j<map_height; j++) {
		for (i=0; i<map_width;) {
			k = GetMapShort(mdat_ptr);
			mdat_ptr += 2;
			if (k > 0) {
				while (k) {
					*my_map_ptr = static_cast <short int>(GetMapShort(mdat_ptr));
					my_map_ptr++; mdat_ptr += 2;
					i++; k--;
				}
			} else {
			if (k < 0) {
				l = GetMapShort(mdat_ptr); mdat_ptr += 2;
				while (k) {
					*my_map_ptr = static_cast <short int>(l);
					my_map_ptr++;
					i++; k++;
				}
			} else {
			} }
		}
	}
	} else {
	if (map_type == 3) {
	for (j=0; j<map_height; j++) {
		for (i=0; i<map_width;) {
			k = GetMapShort(mdat_ptr);
			mdat_ptr += 2;
			if (k > 0) {
				while (k) {
					*my_map_ptr = static_cast <short int>(GetMapShort(mdat_ptr));
					my_map_ptr++; mdat_ptr += 2;
					i++; k--;
				}
			} else {
			if (k < 0) {
				my_map2_ptr = my_map_ptr + GetMapShort(mdat_ptr); mdat_ptr += 2;
				while (k) {
					*my_map_ptr = *my_map2_ptr;
					my_map_ptr++; my_map2_ptr++;
					i++; k++;
				}
			} else {
			} }
		}
	}
	} } } }


	if (lnum == 0) {
		map_ptr = map_map_ptr[lnum];
	}
	return true;
}


int SFMLMappy::MEClickMask(int x, int y, const int xory) {

	x %= map_block_gap_x;
	y %= map_block_gap_y;

	if (x >= map_block_width && xory == 0) return 0;
	if (x >= map_block_width && xory == 1) {
		if (y < map_block_stagger_y) return -1;
		else return 1;
	}
	if (y >= map_block_height && xory == 1) return 1;
	if (y >= map_block_height && xory == 0) {
		if (x < map_block_stagger_x) return -1;
		else return 0;
	}

	switch (map_block_depth) {
		case 8:
			if (sfimage_ptr[map_click_mask].GetPixel(x, y) == sf::Color::Color(0,0,0,255)) {  //suspect
				if (x < (map_block_width/2) && xory == 0) return -1;
				if (x >= (map_block_width/2) && xory == 0) return 0;
				if (y < (map_block_height/2) && xory == 1) return -1;
				if (y >= (map_block_height/2) && xory == 1) return 1;
			}
			return 0;
		default:
			if (sfimage_ptr[map_click_mask].GetPixel(x, y) == sf::Color::Color(255,0,255,255)) { //suspect
				if (x < (map_block_width/2) && xory == 0) return -1;
				if (x >= (map_block_width/2) && xory == 0) return 0;
				if (y < (map_block_height/2) && xory == 1) return -1;
				if (y >= (map_block_height/2) && xory == 1) return 1;
			}
			return 0;
	}
	return 0;
}

int SFMLMappy::GetMapXOffset(int xpix, int ypix) {
	int xb;

	if (map_block_stagger_x || map_block_stagger_y) {
		xpix += (map_block_stagger_x);
		ypix += (map_block_stagger_y);
	}
	xb = xpix/map_block_gap_x;

	if ((map_block_stagger_x || map_block_stagger_y) && map_click_mask) xb += MEClickMask (xpix, ypix, 0);

	if (xb < 0) xb = 0;
	if (xb >= map_width) xb = map_width-1;
	return xb;
}

int SFMLMappy::GetMapYOffset(int xpix, int ypix) {
	int yb;

	if (map_block_stagger_x || map_block_stagger_y) {
		xpix += (map_block_stagger_x);
		ypix += (map_block_stagger_y);
	}
	yb = ypix/map_block_gap_y;

	if ((map_block_stagger_x || map_block_stagger_y) && map_click_mask) {
		yb *= 2;
		yb += MEClickMask(xpix, ypix, 1);
	}

	if (yb < 0) yb = 0;
	if (yb >= map_height) yb = map_height-1;
	return yb;
}

void SFMLMappy::FreeMapMem (void) {
	int i;

	for (i=0;i<8;i++) {
		if (map_map_ptr[i] != NULL) {
			delete[] map_map_ptr[i]; map_map_ptr[i] = NULL;
		}
	}
	map_ptr = NULL;
	for (i=0;i<8;i++) {
		if (map_map_array_ptr[i] != NULL) {
			delete[] map_map_array_ptr[i]; map_map_array_ptr[i] = NULL;
		}
	}

	map_array_ptr = NULL;

	if (map_cmap_ptr != NULL) {
		delete[] map_cmap_ptr; map_cmap_ptr = NULL;
	}
	if (map_block_str_ptr != NULL) {
		delete[] map_block_str_ptr; map_block_str_ptr = NULL;
	}
	if (map_anim_seq_ptr != NULL) {
		delete[] map_anim_seq_ptr; map_anim_seq_ptr = NULL;
	}
	if (map_anim_str_ptr != NULL) {
		delete[] map_anim_str_ptr; map_anim_str_ptr = NULL;
	}

	if (sfsprite_ptr != NULL) { delete[] sfsprite_ptr; sfsprite_ptr = NULL; }
	if (sfimage_ptr != NULL) { delete[] sfimage_ptr; sfimage_ptr = NULL; }
}

// Public Functions
bool SFMLMappy::LoadMap(const char *map_name) {
	unsigned char *id_tag = NULL;
	unsigned char *fmap_ptr = NULL;
	bool mret_val;
	int map_filesize;
	std::ifstream ifsMap;

	map_error = false;

	ifsMap.open(map_name, std::ios::binary);
	if(!ifsMap.is_open()) {
		map_error = true;
		std::cerr << "Error: Unable to open map file!"; return false;
	}

	map_filesize = 0;
	map_error = true;

	// Reading the first 4 bytes to verify that this is a FMP map
	id_tag = new unsigned char[4];
	ifsMap.seekg (0, std::ios::beg);
	ifsMap.read(reinterpret_cast <char *>(id_tag),4);

	if(!strncmp(reinterpret_cast <const char *>(id_tag),"FORM",4)) {
		// The next 4 bytes are the map file size
		ifsMap.read(reinterpret_cast <char *>(id_tag),4);
		map_filesize = GetMapChunkSize(id_tag)+8;
		map_error = false;
	}

	delete[] id_tag;

	if (map_error != false) {
		ifsMap.close();
		std::cerr << "Error: Unable to load map into memory!";
		return false;
	}

	fmap_ptr = new (std::nothrow) unsigned char[map_filesize];
	if (fmap_ptr == 0) { ifsMap.close(); std::cerr << "Error: Unable to allocate additional memory!"; return false; }

	ifsMap.seekg (0, std::ios::beg);
	ifsMap.exceptions ( std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit );
	try {
		ifsMap.read(reinterpret_cast <char *>(fmap_ptr), map_filesize);
	} catch (std::ifstream::failure e) {
		ifsMap.close();
		delete[] fmap_ptr;
		map_error = true;
		std::cerr << "Error: Unable to load map into memory!";
		return false;
	}
	ifsMap.close();

	mret_val = DecodeMap(fmap_ptr);
	delete[] fmap_ptr;

	return mret_val;
}

bool SFMLMappy::DecodeMap(unsigned char *fmap_ptr) {
	unsigned char *fmap_pos_ptr;
	int map_filesize;

	FreeMapMem();
	map_error = false;

	fmap_pos_ptr = fmap_ptr;

	if (strncmp(reinterpret_cast <const char *>(fmap_ptr), "FORM", 4)) {
		map_error = true;
		std::cerr << "Error: Unable to load map into memory";
		return false;
	}

	map_filesize = GetMapChunkSize(fmap_ptr+4);

	if (strncmp(reinterpret_cast <const char *>(fmap_ptr)+8, "FMAP", 4)) {
		map_error = true;
		std::cerr << "Error: Unable to load map into memory";
		return false;
	}

	fmap_pos_ptr += 12;
	map_filesize -= 4;
	while (map_filesize > 0) {
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "MPHD", 4)) DecodeMapMPHD(fmap_pos_ptr);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "CMAP", 4)) DecodeMapCMAP(fmap_pos_ptr);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "BKDT", 4)) DecodeMapBKDT(fmap_pos_ptr);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "ANDT", 4)) DecodeMapANDT(fmap_pos_ptr);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "BGFX", 4)) DecodeMapBGFX(fmap_pos_ptr);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "BODY", 4)) DecodeMapLayer(fmap_pos_ptr, 0);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR1", 4)) DecodeMapLayer(fmap_pos_ptr, 1);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR2", 4)) DecodeMapLayer(fmap_pos_ptr, 2);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR3", 4)) DecodeMapLayer(fmap_pos_ptr, 3);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR4", 4)) DecodeMapLayer(fmap_pos_ptr, 4);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR5", 4)) DecodeMapLayer(fmap_pos_ptr, 5);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR6", 4)) DecodeMapLayer(fmap_pos_ptr, 6);
		if (!strncmp(reinterpret_cast <const char *>(fmap_pos_ptr), "LYR7", 4)) DecodeMapLayer(fmap_pos_ptr, 7);

		map_filesize -= 8;
		map_filesize -= GetMapChunkSize(fmap_pos_ptr+4);
		fmap_pos_ptr += GetMapChunkSize(fmap_pos_ptr+4);
		fmap_pos_ptr += 8;

		if (map_error == true) {
			FreeMapMem();
			return false;
		}
	}
	return true;
}

bool SFMLMappy::LoadMapMAR(char *map_name, int mar_layer) {
	int i, j;
	short int *my_mar_ptr;
	std::ifstream ifsMar;

	if (mar_layer < 0 || mar_layer > 7) return false;

	ifsMar.open(map_name, std::ios::binary);
	if(!ifsMar.is_open()) { ifsMar.close(); return false; }

	if (map_map_ptr[mar_layer] == NULL) {
		map_map_ptr[mar_layer] = new (std::nothrow) short int[map_width*map_height];
	}

	ifsMar.seekg(0, std::ios::beg);
	ifsMar.exceptions( std::ifstream::eofbit | std::ifstream::failbit | std::ifstream::badbit );
	try {
		ifsMar.read(reinterpret_cast <char *>(map_map_ptr[mar_layer]), map_width*map_height*sizeof(short int));
	} catch (std::ifstream::failure e) {
		ifsMar.close();
		return false;
	}

	my_mar_ptr = map_map_ptr[mar_layer];
	j = 0; for (i=0;i<(map_width*map_height);i++) { if (my_mar_ptr[i]&0xF) j = 1; }
	if (j == 0) {
		for (i=0; i<(map_width*map_height); i++) {
			if (my_mar_ptr[i] >= 0) my_mar_ptr[i] /= 32;
			else my_mar_ptr[i] /= 16;
		}
	}
	ifsMar.close();
	return true;
}
bool SFMLMappy::DecodeMapMAR (unsigned char *mr_ptr, int mar_layer) {
	int i, j;
	short int *my_mar_ptr;

	if (mar_layer < 0 || mar_layer > 7) return false;

	if (map_map_ptr[mar_layer] == NULL) {
		map_map_ptr[mar_layer] = new (std::nothrow) short int[map_width*map_height];
	}
	if (map_map_ptr[mar_layer] == 0) {
		map_error = true;
		std::cerr << "Error: Unable to allocate additional memory!"; return false;
	}

	//memcpy(map_map_ptr[mar_layer], mr_ptr, (map_width*map_height*sizeof(short int)));
	std::copy(mr_ptr, mr_ptr+(map_width*map_height*sizeof(short int)), map_map_ptr[mar_layer]);

	my_mar_ptr = map_map_ptr[mar_layer];
	j = 0; for (i=0; i<(map_width*map_height); i++) { if (my_mar_ptr[i]&0xF) j = 1; }
	if (j == 0) {
		for (i=0;i<(map_width*map_height);i++) {
			if (my_mar_ptr[i] >= 0) my_mar_ptr[i] /= 32;
			else my_mar_ptr[i] /= 16;
		}
	}

	return true;
}

bool SFMLMappy::GenerateMapYLookup(void) {
	int i, j;

	for (i=0; i<8; i++) {
		if (map_map_array_ptr[i]!=NULL) { delete[] map_map_array_ptr[i]; map_map_array_ptr[i] = NULL; }
		if (map_map_ptr[i]!=NULL) {
			map_map_array_ptr[i] = new (std::nothrow) short int*[map_height];
			if (map_map_array_ptr[i] == 0) return false;
			for (j=0; j<map_height; j++) map_map_array_ptr[i][j] = (map_map_ptr[i]+(j*map_width));
			if (map_map_ptr[i] == map_ptr) map_array_ptr = map_map_array_ptr[i];
		}
	}
	return false;
}
SFMLMappy::BLKSTR *SFMLMappy::GetMapBlockInPixels(int x, int y) {
	int xp, yp;
	short int *my_map_ptr = NULL;
	ANISTR *my_an_ptr = NULL;

	//if (!map_loaded) { return NULL; }

	if (x < 0 || y < 0 || x >= (map_width*map_block_width) || y >= (map_height*map_block_height)) return NULL;

	xp = x; yp = y;
	x = GetMapXOffset(xp, yp);
	y = GetMapYOffset(xp, yp);

	if (map_array_ptr!= NULL) {
		my_map_ptr = map_array_ptr[y]+x;
	} else {
		my_map_ptr = map_ptr;
		my_map_ptr += x;
		my_map_ptr += y*map_width;
	}
	if (*my_map_ptr>=0) {
		return map_block_str_ptr + *my_map_ptr;
	} else {
		my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
		return map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
	}
}

SFMLMappy::BLKSTR *SFMLMappy::GetMapBlock(const int x, const int y) const {
	short int *my_map_ptr = NULL;
	ANISTR *my_an_ptr = NULL;

	//if (!map_loaded) { return NULL; }

	if (map_array_ptr!= NULL) {
		my_map_ptr = map_array_ptr[y]+x;
	} else {
		my_map_ptr = map_ptr;
		my_map_ptr += x;
		my_map_ptr += y*map_width;
	}
	if (*my_map_ptr>=0) {
		//return ((BLKSTR*)map_block_str_ptr) + *my_map_ptr;
		return map_block_str_ptr + *my_map_ptr;
	} else {
		my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
		//return ((BLKSTR *)map_block_str_ptr) + map_anim_seq_ptr[my_an_ptr->ancuroff];
		return map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
	}
}

void SFMLMappy::SetMapStartPosition(int x, int y) {
	this->map_draw_x = x;
	this->map_draw_y = y;
}

void SFMLMappy::SetMapDimensions(int width, int height) {
	this->map_draw_width = width;
	this->map_draw_height = height;
}

bool SFMLMappy::SetMapBlockInPixels(int x, int y, const int str_value) {
	int xp, yp;
	short int *my_map_ptr = NULL;

	//if (!map_loaded) { return false; }

	if (x < 0 || y < 0 || x >= (map_width*map_block_width) || y >= (map_height*map_block_height)) return false;
	xp = x; yp = y;
	x = GetMapXOffset (xp, yp);
	y = GetMapYOffset (xp, yp);

	if (map_array_ptr!= NULL) {
		my_map_ptr = map_array_ptr[y]+x;
	} else {
		my_map_ptr = map_ptr;
		my_map_ptr += x;
		my_map_ptr += y*map_width;
	}
	*my_map_ptr = str_value;
	return true;
}

bool SFMLMappy::SetMapBlock(const int x, const int y, const int str_value) {
	short int *my_map_ptr = NULL;

	//if (!map_loaded) { return false; }

	if (map_array_ptr!= NULL) {
		my_map_ptr = map_array_ptr[y]+x;
	} else {
		my_map_ptr = map_ptr;
		my_map_ptr += x;
		my_map_ptr += y*map_width;
	}
	*my_map_ptr = str_value;
	return true;
}
int SFMLMappy::GetMapBlockID(const int bl_id, const int user_num) const {
	int i;
	BLKSTR *my_blk_pt = NULL;

	my_blk_pt = map_block_str_ptr;
	if (my_blk_pt == NULL) return -1;

	for (i=0; i<map_num_block_str; i++) {
		switch (user_num) {
			case 1:
				if (my_blk_pt[i].user1 == bl_id) return i;
				break;
			case 2:
				if (my_blk_pt[i].user2 == bl_id) return i;
				break;
			case 3:
				if (my_blk_pt[i].user3 == bl_id) return i;
				break;
			case 4:
				if (my_blk_pt[i].user4 == bl_id) return i;
				break;
			case 5:
				if (my_blk_pt[i].user5 == bl_id) return i;
				break;
			case 6:
				if (my_blk_pt[i].user6 == bl_id) return i;
				break;
			case 7:
				if (my_blk_pt[i].user7 == bl_id) return i;
				break;
		}
	}

	return -1;
}

int SFMLMappy::ChangeMapLayer (const int new_layer) {
	//if (!map_loaded) { return -1; }
	if (new_layer<0 || new_layer>7 || map_map_ptr[new_layer] == NULL) return -1;
	map_ptr = map_map_ptr[new_layer];
	map_array_ptr = map_map_array_ptr[new_layer];
	return new_layer;
}

bool SFMLMappy::UpdateMapAnims(void) const {
	ANISTR *my_an_ptr = NULL;

	if (map_anim_str_ptr==NULL) return true;

	//my_an_ptr = (ANISTR *)map_anim_str_end_ptr;
	my_an_ptr = map_anim_str_end_ptr;
	my_an_ptr--;
	while (my_an_ptr->antype!=-1)
	{
		if (my_an_ptr->antype!=AN_NONE) {
			my_an_ptr->ancount--;
			if (my_an_ptr->ancount<0) {
				my_an_ptr->ancount = my_an_ptr->andelay;
				if (my_an_ptr->antype==AN_LOOPF) {
					if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
						my_an_ptr->ancuroff++;
						if (my_an_ptr->ancuroff==my_an_ptr->anendoff) my_an_ptr->ancuroff = my_an_ptr->anstartoff;
					}
				}
				if (my_an_ptr->antype==AN_LOOPR) {
					if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
						my_an_ptr->ancuroff--;
						if (my_an_ptr->ancuroff==((my_an_ptr->anstartoff)-1))
						my_an_ptr->ancuroff = (my_an_ptr->anendoff)-1;
					}
				}
				if (my_an_ptr->antype==AN_ONCE) {
					if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
						my_an_ptr->ancuroff++;
						if (my_an_ptr->ancuroff==my_an_ptr->anendoff) {
							my_an_ptr->antype = AN_ONCES;
							my_an_ptr->ancuroff = my_an_ptr->anstartoff;
						}
					}
				}
				if (my_an_ptr->antype==AN_ONCEH) {
					if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
						if (my_an_ptr->ancuroff!=((my_an_ptr->anendoff)-1)) my_an_ptr->ancuroff++;
					}
				}
				if (my_an_ptr->antype==AN_PPFF) {
					if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
						my_an_ptr->ancuroff++;
						if (my_an_ptr->ancuroff==my_an_ptr->anendoff) {
							my_an_ptr->ancuroff -= 2;
							my_an_ptr->antype = AN_PPFR;
							if (my_an_ptr->ancuroff<my_an_ptr->anstartoff) my_an_ptr->ancuroff++;
						}
					}
				} else {
					if (my_an_ptr->antype==AN_PPFR)	{
						if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
							my_an_ptr->ancuroff--;
							if (my_an_ptr->ancuroff==((my_an_ptr->anstartoff)-1)) {
								my_an_ptr->ancuroff += 2;
								my_an_ptr->antype = AN_PPFF;
								if (my_an_ptr->ancuroff>my_an_ptr->anendoff) my_an_ptr->ancuroff --;
							}
						}
					}
				}
				if (my_an_ptr->antype==AN_PPRR) {
					if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
						my_an_ptr->ancuroff--;
						if (my_an_ptr->ancuroff==((my_an_ptr->anstartoff)-1)) {
							my_an_ptr->ancuroff += 2;
							my_an_ptr->antype = AN_PPRF;
							if (my_an_ptr->ancuroff>my_an_ptr->anendoff) my_an_ptr->ancuroff--;
						}
					}
				} else {
					if (my_an_ptr->antype==AN_PPRF)	{
						if (my_an_ptr->anstartoff!=my_an_ptr->anendoff) {
							my_an_ptr->ancuroff++;
							if (my_an_ptr->ancuroff==my_an_ptr->anendoff) {
								my_an_ptr->ancuroff -= 2;
								my_an_ptr->antype = AN_PPRR;
								if (my_an_ptr->ancuroff<my_an_ptr->anstartoff) my_an_ptr->ancuroff++;
							}
						}
					}
				}
			}
		}
		my_an_ptr--;
	}
	return true;
}

void SFMLMappy::DrawMapBG(sf::RenderWindow &App, int mapxo, int mapyo) const {
	int i, j, mapvclip, maphclip;
	int mbgx, mbgy; //, temp1, temp2;
	short int *my_map_ptr = NULL;
	short int *my_map2_ptr = NULL;
	BLKSTR *blk_data_ptr = NULL;
	ANISTR *my_an_ptr = NULL;

	mapxo -= map_block_stagger_x;
	mapyo -= map_block_stagger_y;
	my_map_ptr = map_ptr;
	if (map_block_stagger_x || map_block_stagger_y) {
		my_map_ptr += (mapxo/map_block_gap_x)+((mapyo/map_block_gap_y)*map_width*2);
		mbgx = map_block_gap_x;
		mbgy = map_block_gap_y;
	} else {
		my_map_ptr += (mapxo/map_block_gap_x)+((mapyo/map_block_gap_y)*map_width);
		mbgx = 0;
		mbgy = 0;
	}
	mapvclip = mapyo%map_block_gap_y;
	maphclip = mapxo%map_block_gap_x;

	my_map2_ptr = my_map_ptr;
	for (j=((map_draw_y-mapvclip)-mbgy);j<((map_draw_y+map_draw_height));j+=map_block_gap_y) {
		for (i=((map_draw_x-maphclip)-mbgx);i<((map_draw_x+map_draw_width));i+=map_block_gap_x) {
			if (*my_map_ptr>=0) {
				blk_data_ptr = map_block_str_ptr + *my_map_ptr;
			} else {
				my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
				blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
			}
			/*if (map_block_stagger_x || map_block_stagger_y) {
				// Don't bother drawing tile 0
				if (blk_data_ptr->bgoff != 0) {
					sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
				}
			} else {*/
			if (blk_data_ptr->bgoff != 0) {
				sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j));
				App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
			}
			//}
			my_map_ptr++;
		}
		if (map_block_stagger_x || map_block_stagger_y) {
			my_map2_ptr += map_width;
			my_map_ptr = my_map2_ptr;
			for (i=(((map_draw_x-maphclip)-mbgx)+map_block_stagger_x);i<((map_draw_x+map_draw_width));i+=map_block_gap_x) {
				if (*my_map_ptr>=0) {
					blk_data_ptr = map_block_str_ptr + *my_map_ptr;
				} else {
					my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
					blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
				}
				// Don't bother drawing tile 0
				if (blk_data_ptr->bgoff != 0) {
					sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j+map_block_stagger_y));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
				}
				my_map_ptr++;
			}
		}
		my_map2_ptr += map_width;
		my_map_ptr = my_map2_ptr;
	}
}

/*
void SFMLMappy::DrawMapBG(sf::RenderWindow &App, int mapxo, int mapyo) const {
	int i, j, mapvclip, maphclip;
	int mbgx, mbgy, temp1, temp2;
	short int *my_map_ptr = NULL;
	short int *my_map2_ptr = NULL;
	BLKSTR *blk_data_ptr = NULL;
	ANISTR *my_an_ptr = NULL;

	mapxo -= map_block_stagger_x;
	mapyo -= map_block_stagger_y;
	my_map_ptr = map_ptr;
	if (map_block_stagger_x || map_block_stagger_y) {
		my_map_ptr += (mapxo/map_block_gap_x)+((mapyo/map_block_gap_y)*map_width*2);
		mbgx = map_block_gap_x;
		mbgy = map_block_gap_y;
	} else {
		my_map_ptr += (mapxo/map_block_gap_x)+((mapyo/map_block_gap_y)*map_width);
		mbgx = 0;
		mbgy = 0;
	}
	mapvclip = mapyo%map_block_gap_y;
	maphclip = mapxo%map_block_gap_x;

	my_map2_ptr = my_map_ptr;
	for (j=((map_draw_y-mapvclip)-mbgy);j<((map_draw_y+map_draw_height));j+=map_block_gap_y) {
		for (i=((map_draw_x-maphclip)-mbgx);i<((map_draw_x+map_draw_width));i+=map_block_gap_x) {
			if (*my_map_ptr>=0) {
				blk_data_ptr = map_block_str_ptr + *my_map_ptr;
			} else {
				my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
				blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
			}
			/*if (map_block_stagger_x || map_block_stagger_y) {
				// Don't bother drawing tile 0
				if (blk_data_ptr->bgoff != 0) {
					sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
				}
			} else {*/ /*
			if (blk_data_ptr->bgoff != 0) {
				if (i<map_draw_x || j<map_draw_y) {
					if (i<map_draw_x) {
						temp1 = map_draw_x-i;
						sfsprite_ptr[blk_data_ptr->bgoff].SetX(static_cast<float>(map_draw_x));
					} else {
						temp1 = 0;
						sfsprite_ptr[blk_data_ptr->bgoff].SetX(static_cast<float>(i));
					}
					if(j<map_draw_y) {
						temp2 = map_draw_y-j;
						sfsprite_ptr[blk_data_ptr->bgoff].SetY(static_cast<float>(map_draw_y));
					} else {
						temp2 = 0;
						sfsprite_ptr[blk_data_ptr->bgoff].SetY(static_cast<float>(j));
					}
					sfsprite_ptr[blk_data_ptr->bgoff].SetSubRect(sf::IntRect(temp1,temp2,map_block_width,map_block_height));
					//sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(map_draw_x), static_cast<float>(j));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
					sfsprite_ptr[blk_data_ptr->bgoff].SetSubRect(sf::IntRect(0,0,map_block_width,map_block_height));
				} else if (i+map_block_width>map_draw_x+map_draw_width || j+map_block_height>map_draw_y+map_draw_height) {
					if (i+map_block_width>map_draw_x+map_draw_width) {
						temp1 = map_block_width-((map_draw_x+map_draw_width)-(i+map_block_width));
						//sfsprite_ptr[blk_data_ptr->bgoff].SetX(static_cast<float>(map_draw_x));
					} else {
						temp1 = map_block_width;
						//sfsprite_ptr[blk_data_ptr->bgoff].SetX(static_cast<float>(i));
					}
					if(j+map_block_height>map_draw_y+map_draw_height) {
						temp2 = map_block_height-((map_draw_y+map_draw_height)-(j+map_block_height));
						//sfsprite_ptr[blk_data_ptr->bgoff].SetY(static_cast<float>(map_draw_y));
					} else {
						temp2 = map_block_height;
						//sfsprite_ptr[blk_data_ptr->bgoff].SetY(static_cast<float>(j));
					}
					std::cout << temp1 << " ";
					sfsprite_ptr[blk_data_ptr->bgoff].SetSubRect(sf::IntRect(0,0,temp1,temp2));
					sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
					sfsprite_ptr[blk_data_ptr->bgoff].SetSubRect(sf::IntRect(0,0,map_block_width,map_block_height));
				} else {
					sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
				}
			}
			//}
			my_map_ptr++;
		}
		if (map_block_stagger_x || map_block_stagger_y) {
			my_map2_ptr += map_width;
			my_map_ptr = my_map2_ptr;
			for (i=(((map_draw_x-maphclip)-mbgx)+map_block_stagger_x);i<((map_draw_x+map_draw_width));i+=map_block_gap_x) {
				if (*my_map_ptr>=0) {
					blk_data_ptr = map_block_str_ptr + *my_map_ptr;
				} else {
					my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
					blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
				}
				// Don't bother drawing tile 0
				if (blk_data_ptr->bgoff != 0) {
					sfsprite_ptr[blk_data_ptr->bgoff].SetPosition(static_cast<float>(i), static_cast<float>(j+map_block_stagger_y));
					App.Draw(sfsprite_ptr[blk_data_ptr->bgoff]);
				}
				my_map_ptr++;
			}
		}
		my_map2_ptr += map_width;
		my_map_ptr = my_map2_ptr;
	}
}
*/

void SFMLMappy::DrawMapBG(sf::RenderWindow &App, const int mapxo, const int mapyo, const int mapx, const int mapy, const int mapw, const int maph) {
	map_draw_x=mapx;
	map_draw_y=mapy;
	map_draw_width=mapw;
	map_draw_height=maph;

	DrawMapBG(App, mapxo, mapyo);
}

void SFMLMappy::DrawMapFG(sf::RenderWindow &App, int mapxo, int mapyo, const int mapfg) const {
	int i, j, mapvclip, maphclip;
	int mbgx, mbgy;
	short int *my_map_ptr = NULL;
	short int *my_map2_ptr = NULL;
	long int image_index = NULL;
	BLKSTR *blk_data_ptr = NULL;
	ANISTR *my_an_ptr = NULL;

	mapxo -= map_block_stagger_x;
	mapyo -= map_block_stagger_y;
	my_map_ptr = map_ptr;
	if (map_block_stagger_x || map_block_stagger_y) {
		my_map_ptr += (mapxo/map_block_gap_x)+((mapyo/map_block_gap_y)*map_width*2);
		mbgx = map_block_gap_x;
		mbgy = map_block_gap_y;
	} else {
		my_map_ptr += (mapxo/map_block_gap_x)+((mapyo/map_block_gap_y)*map_width);
		mbgx = 0;
		mbgy = 0;
	}
	mapvclip = mapyo%map_block_gap_y;
	maphclip = mapxo%map_block_gap_x;

	my_map2_ptr = my_map_ptr;
	for (j=((map_draw_y-mapvclip)-mbgy);j<((map_draw_y+map_draw_height));j+=map_block_gap_y) {
		for (i=((map_draw_x-maphclip)-mbgx);i<((map_draw_x+map_draw_width));i+=map_block_gap_x) {
			if (*my_map_ptr>=0) {
				blk_data_ptr = map_block_str_ptr + *my_map_ptr;
			} else {
				my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
				blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
			}

			if (!mapfg) {
				image_index = blk_data_ptr->fgoff;
			} else if(mapfg == 1) {
				image_index = blk_data_ptr->fgoff2;
			} else {
				image_index = blk_data_ptr->fgoff3;
			}
			if (image_index > 0) {
				sfsprite_ptr[image_index].SetPosition(static_cast<float>(i), static_cast<float>(j));
				App.Draw(sfsprite_ptr[image_index]);
			}
			my_map_ptr++;
		}
		if (map_block_stagger_x || map_block_stagger_y) {
			my_map2_ptr += map_width;
			my_map_ptr = my_map2_ptr;
			for (i=(((map_draw_x-maphclip)-mbgx)+map_block_stagger_x);i<((map_draw_x+map_draw_width));i+=map_block_gap_x) {
				if (*my_map_ptr>=0) {
					blk_data_ptr = map_block_str_ptr + *my_map_ptr;
				} else {
					my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
					blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
				}

				if (!mapfg) {
					image_index = blk_data_ptr->fgoff;
				} else if(mapfg == 1) {
					image_index = blk_data_ptr->fgoff2;
				} else {
					image_index = blk_data_ptr->fgoff3;
				}
				if (image_index > 0) {
					sfsprite_ptr[image_index].SetPosition(static_cast<float>(i), static_cast<float>(j+map_block_stagger_y));
					App.Draw(sfsprite_ptr[image_index]);
				}
				my_map_ptr++;
			}
		}
		my_map2_ptr += map_width;
		my_map_ptr = my_map2_ptr;
	}
}

void SFMLMappy::DrawMapFG(sf::RenderWindow &App, const int mapxo, const int mapyo, const int mapx, const int mapy, const int mapw, const int maph, const int mapfg) {
	map_draw_x=mapx;
	map_draw_y=mapy;
	map_draw_width=mapw;
	map_draw_height=maph;

	DrawMapFG(App, mapxo, mapyo, mapfg);
}


void SFMLMappy::DrawMapRow(sf::RenderWindow &App, int mapxo, int mapyo, const int mapx, const int mapy,	const int mapw, const int maph, const int maprw, void (*cellcall) (int cx, int cy, int dx, int dy)) {
	int i, j, mapvclip, maphclip;
	int mbgx, mbgy, bfield, bysub;
	long int field;
	int cx, cy;
	short int *my_map_ptr = NULL;
	short int *my_map2_ptr = NULL;
	BLKSTR *blk_data_ptr = NULL;
	ANISTR *my_an_ptr = NULL;
	sf::Sprite map_gfx_ptr;

	if (((mapyo/map_block_gap_y)+maprw) >= map_height) return;

	if (map_block_stagger_x || map_block_stagger_y) {
		mapxo -= map_block_stagger_x;
		mapyo -= map_block_stagger_y;
		if ((((mapyo/map_block_gap_y)*2)+maprw) >= (map_height-1)) return;
	}

	//set_clip (mapdestpt, mapx, mapy, mapx+mapw-1, mapy+maph-1);
	my_map_ptr = map_ptr;
	mapvclip = mapyo%map_block_gap_y;
	maphclip = mapxo%map_block_gap_x;
	j = (mapy-mapvclip); i = 0;
	if (map_block_stagger_x || map_block_stagger_y) {
		cx = mapxo/map_block_gap_x;
		cy = (((mapyo/map_block_gap_y)*2)+maprw);
		my_map_ptr += (cx)+(cy*map_width);
		mbgx = map_block_gap_x;
		mbgy = map_block_gap_y;
		j -= mbgy;
		j += ((maprw/2)*map_block_gap_y);
		if (maprw&1) { j += map_block_stagger_y; i = map_block_stagger_x; }
	} else {
		cx = mapxo/map_block_gap_x;
		cy = ((mapyo/map_block_gap_y)+maprw);
		my_map_ptr += (cx)+(cy*map_width);
		mbgx = 0;
		mbgy = 0;
		j += (maprw*map_block_gap_y);
	}

	my_map2_ptr = my_map_ptr;
	for (i+=((mapx-maphclip)-mbgx);i<((mapx+mapw));i+=map_block_gap_x) {
		if (cellcall != NULL) cellcall (cx, cy, i, j);
		if (*my_map_ptr>=0) blk_data_ptr = map_block_str_ptr + *my_map_ptr;
		else {
			my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
			blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
		}
		bfield = 1; bysub = 0;
		do {
			if (!bfield) blk_data_ptr++;
			field = 0;
			for (;bfield<4; bfield++) {
				switch (bfield) {
					case 0: {
								field = blk_data_ptr->bgoff;
								map_gfx_ptr = sfsprite_ptr[field];
							}
							break;
					case 1: {
								field = blk_data_ptr->fgoff;
								map_gfx_ptr = sfsprite_ptr[field];
							}
							break;
					case 2: {
								field = blk_data_ptr->fgoff2;
								map_gfx_ptr = sfsprite_ptr[field];
							}
							break;
					default:
					case 3: {
								field = blk_data_ptr->fgoff3;
								map_gfx_ptr = sfsprite_ptr[field];
							}
							break;
				}
				if (field > 0) {
					if (blk_data_ptr->unused2 && !blk_data_ptr->unused3) {
						map_gfx_ptr.SetSubRect(sf::IntRect(0,0,map_block_width/2,map_block_height));
						map_gfx_ptr.SetPosition(static_cast<float>(i), static_cast<float>(j-bysub));
						App.Draw(map_gfx_ptr);
						map_gfx_ptr.SetSubRect(sf::IntRect(0,0,map_block_width,map_block_height));
					} else {
						if (!blk_data_ptr->unused2 && blk_data_ptr->unused3) {
							map_gfx_ptr.SetSubRect(sf::IntRect(0,0,map_block_width/2,map_block_height));
							map_gfx_ptr.SetPosition(static_cast<float>(i), static_cast<float>(j-bysub));
							App.Draw(map_gfx_ptr);
							map_gfx_ptr.SetSubRect(sf::IntRect(0,0,map_block_width,map_block_height));
						} else {
							map_gfx_ptr.SetPosition(static_cast<float>(i), static_cast<float>(j-bysub));
							App.Draw(map_gfx_ptr);
						}
					}
				}
				bysub += map_block_height;
			}
			bfield = 0;
		} while (blk_data_ptr->unused1);
		my_map_ptr++; cx++;
	}
	//set_clip (mapdestpt, mycl, myct, mycr+1, mycb+1);
}

void SFMLMappy::MakeMapParallaxBitmap(sf::Image &Image) const {
	sf::Sprite parbm_sprite;

	sf::Image New_Image;
	New_Image.Create(Image.GetWidth()+map_block_width,Image.GetHeight()+map_block_height,sf::Color::Color(0,0,0,255));
	New_Image.Copy(Image,0,0);
	New_Image.Copy(Image,0,Image.GetHeight());
	New_Image.Copy(New_Image,Image.GetWidth(),0);
	Image = New_Image;
	Image.SetSmooth(false);
}

void SFMLMappy::DrawMapParallax(sf::RenderWindow &App, sf::Sprite &Parbm, int parbm_w, int parbm_h, int mapxo, int mapyo) const {
	int i, i2, j;
	int paraxo, paraxo2, parayo;
	short int *my_map_ptr, *my_map2_ptr;
	BLKSTR *blk_data_ptr;
	ANISTR *my_an_ptr;

	if (map_block_stagger_x || map_block_stagger_y) return;

	//set_clip (mapdestpt, mapx, mapy, mapx+mapw-1, mapy+maph-1);

	my_map_ptr = map_ptr;
	my_map_ptr += (mapxo/map_block_width)+((mapyo/map_block_height)*map_width);

	paraxo = ((mapxo-(mapxo%map_block_width))%(parbm_w-map_block_width))-((mapxo/2)%(parbm_w-map_block_width));
	parayo = ((mapyo-(mapyo%map_block_height))%(parbm_h-map_block_height))-((mapyo/2)%(parbm_h-map_block_height));
	while (paraxo < 0) paraxo += (parbm_w-map_block_width);
	while (parayo < 0) parayo += (parbm_h-map_block_height);

	i = map_draw_x-(mapxo%map_block_width);
	j = map_draw_y-(mapyo%map_block_height);

	i2 = i; paraxo2 = paraxo; my_map2_ptr = my_map_ptr;

	while (j < (map_draw_y+map_draw_height)) {
		while (i < (map_draw_x+map_draw_width)) {
			if (*my_map_ptr>=0) {
				blk_data_ptr = map_block_str_ptr + *my_map_ptr;
			} else {
				my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
				blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
			}
			if (blk_data_ptr->trigger) {
				//blit (parbm, mapdestpt, paraxo, parayo, i, j, mapblockwidth, mapblockheight);
				Parbm.SetSubRect(sf::IntRect(paraxo,parayo,paraxo+map_block_width,parayo+map_block_height));
				Parbm.SetPosition(static_cast<float>(i), static_cast<float>(j));
				App.Draw(Parbm);

			}
			paraxo += map_block_width;
			if (paraxo >= (parbm_w-map_block_width)) paraxo -= (parbm_w-map_block_width);
			i += map_block_width; my_map_ptr++;
		}
		parayo += map_block_height;
		if (parayo >= (parbm_h-map_block_height)) parayo -= (parbm_h-map_block_height);
		i = i2; paraxo = paraxo2; my_map2_ptr += map_width; my_map_ptr = my_map2_ptr;
		j += map_block_height;
	}
	//set_clip (mapdestpt, mycl, myct, mycr+1, mycb+1);
}

void SFMLMappy::DrawMapParallax(sf::RenderWindow &App, sf::Sprite &Parbm, int parbm_w, int parbm_h, int mapxo, int mapyo, int mapx, int mapy, int mapw, int maph) const {
	int i, i2, j;
	int paraxo, paraxo2, parayo;
	short int *my_map_ptr, *my_map2_ptr;
	BLKSTR *blk_data_ptr;
	ANISTR *my_an_ptr;

	if (map_block_stagger_x || map_block_stagger_y) return;

	//set_clip (mapdestpt, mapx, mapy, mapx+mapw-1, mapy+maph-1);

	my_map_ptr = map_ptr;
	my_map_ptr += (mapxo/map_block_width)+((mapyo/map_block_height)*map_width);

	paraxo = ((mapxo-(mapxo%map_block_width))%(parbm_w-map_block_width))-((mapxo/2)%(parbm_w-map_block_width));
	parayo = ((mapyo-(mapyo%map_block_height))%(parbm_h-map_block_height))-((mapyo/2)%(parbm_h-map_block_height));
	while (paraxo < 0) paraxo += (parbm_w-map_block_width);
	while (parayo < 0) parayo += (parbm_h-map_block_height);

	i = mapx-(mapxo%map_block_width);
	j = mapy-(mapyo%map_block_height);

	i2 = i; paraxo2 = paraxo; my_map2_ptr = my_map_ptr;

	while (j < (mapy+maph)) {
		while (i < (mapx+mapw)) {
			if (*my_map_ptr>=0) {
				blk_data_ptr = map_block_str_ptr + *my_map_ptr;
			} else {
				my_an_ptr = map_anim_str_end_ptr + *my_map_ptr;
				blk_data_ptr = map_block_str_ptr + map_anim_seq_ptr[my_an_ptr->ancuroff];
			}
			if (blk_data_ptr->trigger) {
				//blit (parbm, mapdestpt, paraxo, parayo, i, j, mapblockwidth, mapblockheight);
				Parbm.SetSubRect(sf::IntRect(paraxo,parayo,paraxo+map_block_width,parayo+map_block_height));
				Parbm.SetPosition(static_cast<float>(i), static_cast<float>(j));
				App.Draw(Parbm);

			}
			paraxo += map_block_width;
			if (paraxo >= (parbm_w-map_block_width)) paraxo -= (parbm_w-map_block_width);
			i += map_block_width; my_map_ptr++;
		}
		parayo += map_block_height;
		if (parayo >= (parbm_h-map_block_height)) parayo -= (parbm_h-map_block_height);
		i = i2; paraxo = paraxo2; my_map2_ptr += map_width; my_map_ptr = my_map2_ptr;
		j += map_block_height;
	}
	//set_clip (mapdestpt, mycl, myct, mycr+1, mycb+1);
}

short int SFMLMappy::GetMapWidth(void) const {
	return map_width;
}

short int SFMLMappy::GetMapHeight(void) const {
	return map_height;
}

short int SFMLMappy::GetMapBlockWidth(void) const {
	return map_block_width;
}

short int SFMLMappy::GetMapBlockHeight(void) const {
	return map_block_height;
}

short int SFMLMappy::GetMapDepth(void) const {
	return map_block_depth;
}

int SFMLMappy::GetMapBlockGapX(void) const {
	return map_block_gap_x;
}

int SFMLMappy::GetMapBlockGapY(void) const {
	return map_block_gap_y;
}

int SFMLMappy::GetMapBlockStaggerX(void) const {
	return map_block_stagger_x;
}

int SFMLMappy::GetMapBlockStaggerY(void) const {
	return map_block_stagger_y;
}
