/* Mappy playback library class
 * SFML 1.6 Port by Brian Glenn (Breakman79) - bglenn01@gmail.com
 * Ver 1.00 Beta (March 2010)
 *
 * Based on Allegro(R11C) and OpenGL playback libraries by
 * original Mappy creator Robin Burrows - rburrows@bigfoot.com
 *
 * Mappy Editor can be found at http://www.tilemap.co.uk/mappy.php
 */


/*
WHAT WORKS!
 - Displaying Regular Tilemaps
 - Displaying Isometric Tilemaps
 - Displaying Hexagonal TileMaps
 - Displaying Parallax Background

WHAT DOESN'T WORK!
 - Map Edge Clipping (Not an issue if you display the map fullscreen.  A todo for the future)
 - DrawMapBGT (Redundant at the moment since every sprite already has alpha transparency enabled by default)

UNTESTED
 - Loading and Decoding of MAR files
 - Some of the different map depths (8, 24, and 32-bit seem to work as far as I can tell)
 - I haven't really looked hard at most of the GetMapBlock functions, they should work though

TODO
 - Perhaps some more error checking for the methods to fail gracefully if there is a problem loading the map data rather than a
   nasty crash to desktop or an out of memory error if you don't check the GetErrorNum accessor (Anything > 0 shows a problem)

I slightly modified most of the function names and variables to match the syntax we use in PHP at my office.  Hopefully no one
minds too much.  For the most other than the names is should looks very similar to the Allegro version which is what I first used
almost 12 years ago and I found it the easiest to port from.  Only the DrawMapParallax method changed with the addition of
two extra parameters for the new width and height for the parallax bitmap after it has been modified by MakeMapParallaxBitmap.
If SFML has a method of returning image size for a sprite, let me know so I can change it so they don't need to be passed in.

DOCUMENTATION
At the moment I recommend going to the Mappy website and downloading a copy of the Allegro playback library and looking at the
README file.  The function description is very similiar to these.

Bug reports or thoughts on perhaps doing something a better way are greatly appreciated.
*/

#ifndef SFMLMAPPY_H
#define SFMLMAPPY_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

class SFMLMappy {
private:
	bool DecodeMapMPHD(unsigned char *mdat_ptr);				// Decodes basic header info (map height, width, color depth, etc)
	bool DecodeMapCMAP(unsigned char *mdat_ptr);				// Decodes palette information for 8-bit depth maps
	bool DecodeMapBKDT(unsigned char *mdat_ptr);				// Decodes the data block for each individual tile and fills an array of BLKSTRs
	bool DecodeMapANDT(unsigned char *mdat_ptr);				// Decode Animation blocks
	bool DecodeMapBGFX(unsigned char *mdat_ptr);				// Decodes the saved tile graphics
	bool DecodeMapLayer(unsigned char *mdat_ptr, int lnum);		// Decodes each layer passed to it by lnum
	int GetMapChunkSize(const unsigned char *loc_ptr) const;	// Return chunk size by reading next 4 bytes after pointer location
	int GetMapShort(const unsigned char *loc_ptr) const;		// Used for returning an integer stored in 2 bytes of binary
	int GetMapLong(const unsigned char *loc_ptr) const;			// Used for returning an integer stored in 4 bytes of binary
	int MEClickMask(int x, int y, const int xory);				// Used for iso and hex maps
	void InitMapAnims(void) const;								// Initializes the map animations
	void InitMapClass(void);									// Sets up default values in Constructor
	void FreeMapMem(void);										// Cleans up memory used by Mappy

	typedef struct {						/* Structure for data blocks */
		long int bgoff, fgoff;				/* offsets from start of graphic blocks */
		long int fgoff2, fgoff3; 			/* more overlay blocks */
		unsigned long int user1, user2;		/* user long data */
		unsigned short int user3, user4;	/* user short data */
		unsigned char user5, user6, user7;	/* user byte data */
		unsigned char tl : 1;				/* bits for collision detection */
		unsigned char tr : 1;
		unsigned char bl : 1;
		unsigned char br : 1;
		unsigned char trigger : 1;			/* bit to trigger an event */
		unsigned char unused1 : 1;
		unsigned char unused2 : 1;
		unsigned char unused3 : 1;
	} BLKSTR;

	typedef struct {			/* Animation control structure */
		signed char antype;		/* Type of anim, AN_? */
		signed char andelay;	/* Frames to go before next frame */
		signed char ancount;	/* Counter, decs each frame, till 0, then resets to andelay */
		signed char anuser;		/* User info */
		long int ancuroff;		/* Points to current offset in list */
		long int anstartoff;	/* Points to start of blkstr offsets list, AFTER ref. blkstr offset */
		long int anendoff;		/* Points to end of blkstr offsets list */
	} ANISTR;

	BLKSTR *map_block_str_ptr;
	ANISTR *map_anim_str_ptr;
	ANISTR *map_anim_str_end_ptr;
	int *map_anim_seq_ptr;
	unsigned char *map_cmap_ptr;
	short int *map_ptr;
	short int **map_array_ptr;
	short int *map_map_ptr[8];
	short int **map_map_array_ptr[8];
	sf::Image *sfimage_ptr;		// Pointer to store image blocks
	sf::Sprite *sfsprite_ptr;

	bool map_error;
	int map_type, map_is_lsb, map_click_mask;
	short int map_width, map_height;
	short int map_block_width, map_block_height, map_block_depth;
	int map_block_str_size, map_num_block_str, map_num_block_gfx, map_num_anim_str;
	int map_block_gap_x, map_block_gap_y, map_block_stagger_x, map_block_stagger_y;

	int map_draw_x, map_draw_y, map_draw_width, map_draw_height;

	// Mappy Static Constants
	static const unsigned short int MTRANSP8			= 0;	// Transparency index for paletted screen (0 to 255)
	static const unsigned short int MTRANSPR			= 0xFF;	// 8bit RED transparency value for high/true color
	static const unsigned short int MTRANSPG			= 0x00;	// 8bit GREEN transparency value for high/true color
	static const unsigned short int MTRANSPB			= 0xFF;	// 8bit BLUE transparency value for high/true color

	static const unsigned short int AN_END				= -1;	// Animation types, AN_END = end of anims
	static const unsigned short int AN_NONE				= 0;	// No anim defined
	static const unsigned short int AN_LOOPF			= 1;	// Loops from start to end, then jumps to start etc
	static const unsigned short int AN_LOOPR			= 2;	// As above, but from end to start
	static const unsigned short int AN_ONCE				= 3;	// Only plays once
	static const unsigned short int AN_ONCEH			= 4;	// Only plays once, but holds end frame
	static const unsigned short int AN_PPFF				= 5;	// Ping Pong start-end-start-end-start etc
	static const unsigned short int AN_PPRR				= 6;	// Ping Pong end-start-end-start-end etc
	static const unsigned short int AN_PPRF				= 7;	// Used internally by playback
	static const unsigned short int AN_PPFR				= 8;	// Used internally by playback
	static const unsigned short int AN_ONCES			= 9;	// Used internally by playback

public:
	SFMLMappy();
	SFMLMappy(const char *map_name);
	SFMLMappy(const char *map_name, int x, int y, int width, int height);
	~SFMLMappy();
	bool LoadMap(const char *map_name);
	bool DecodeMap(unsigned char *fmap_ptr);			// Loops though the mapfile searching for chunks to send off to the other decode functions
	bool LoadMapMAR(char *mname, int mar_layer);
	bool DecodeMapMAR(unsigned char *mr_ptr, int mar_layer);
	int ChangeMapLayer(const int new_layer);
	bool UpdateMapAnims(void) const;
	void SetMapStartPosition(int x, int y);
	void SetMapDimensions(int width, int height);
	void DrawMapBG(sf::RenderWindow &App, int mapxo, int mapyo) const;
	void DrawMapBG(sf::RenderWindow &App, const int mapxo, const int mapyo, const int mapx, const int mapy, const int mapw, const int maph);
	void DrawMapFG(sf::RenderWindow &App, int mapxo, int mapyo, const int mapfg) const;
	void DrawMapFG(sf::RenderWindow &App, const int mapxo, const int mapyo, const int mapx, const int mapy, const int mapw, const int maph, const int mapfg);
	void DrawMapRow(sf::RenderWindow &App, int mapxo, int mapyo, const int mapx, const int mapy, const int mapw, const int maph, const int maprw, void (*cellcall) (int cx, int cy, int dx, int dy));
	bool GenerateMapYLookup(void);
	int GetMapXOffset(int xpix, int ypix);
	int GetMapYOffset(int xpix, int ypix);
	bool SetMapBlockInPixels(int x, int y, const int str_value);
	bool SetMapBlock(const int x, const int y, const int str_value);
	int GetMapBlockID(const int bl_id, const int user_num) const;
	BLKSTR *GetMapBlock(const int x, const int y) const;
	BLKSTR *GetMapBlockInPixels(int x, int y);
	void MakeMapParallaxBitmap(sf::Image &Image) const;
	void DrawMapParallax(sf::RenderWindow &App, sf::Sprite &Parbm, int parbm_w, int parbm_h, int mapxo, int mapyo) const;
	void DrawMapParallax(sf::RenderWindow &App, sf::Sprite &Parbm, int parbm_w, int parbm_h, int mapxo, int mapyo, int mapx, int mapy, int mapw, int maph) const;

	// Accessors
	short int GetMapWidth(void) const;
	short int GetMapHeight(void) const;
	short int GetMapBlockWidth(void) const;
	short int GetMapBlockHeight(void) const;
	short int GetMapDepth(void) const;
	int GetMapBlockGapX(void) const;
	int GetMapBlockGapY(void) const;
	int GetMapBlockStaggerX(void) const;
	int GetMapBlockStaggerY(void) const;
};
#endif
