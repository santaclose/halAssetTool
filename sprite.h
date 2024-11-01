#pragma once

#include "types.h"

enum bmformat : u8 {
	G_IM_FMT_RGBA = 0,
	G_IM_FMT_YUV = 1,
	G_IM_FMT_CI = 2,
	G_IM_FMT_IA = 3,
	G_IM_FMT_I = 4
};
enum bmtxsize : u8 {
	G_IM_SIZ_4b = 0,
	G_IM_SIZ_8b = 1,
	G_IM_SIZ_16b = 2,
	G_IM_SIZ_32b = 3,
	G_IM_SIZ_4c = 4,
	G_IM_SIZ_DD = 5
};

struct Bitmap {
	s16	width;		/* Size across to draw in texels */
	/* Done if width = 0		*/

	s16	width_img;	/* Size across of bitmap in texels */
	/* Done if width = 0		*/

	s16	s;		/* Horizontal offset into bitmap */
	/* if (s > width), then load only! */

	s16	t;		/* Vertical offset into base	*/

	relocPointer buf;	/* Pointer to bitmap data	*/
	/* Don't re-load if new buf	*/
	/* is the same as the old one   */
	/* Skip if NULL */

	s16	actualHeight;	/* True Height of this bitmap piece */

	s16	LUToffset;	/* LUT base index		*/
};

struct Sprite {
	s16	x, y;		/* Target position		*/

	s16	width, height;	/* Target size			*/

	f32	scalex, scaley;	/* Texel to Pixel scale factor	*/

	s16	expx, expy;	/* Explosion spacing		*/

	u16 	attr;		/* Attribute Flags		*/
	s16	zdepth;		/* Z Depth 			*/

	u8	red;		/* Red component		*/
	u8	green;		/* Green component		*/
	u8	blue;		/* Blue component		*/
	u8	alpha;		/* Alpha component		*/

	s16	startTLUT;	/* Lookup Table Entry Starting index */
	s16	nTLUT;		/* Total number of Lookup Table Entries */

	relocPointer LUT;		/* Pointer to Lookup Table	*/

	s16	istart;		/* Starting bitmap index	*/
	s16	istep;		/* Bitmaps index step (see SP_INCY) */
	/* if 0, then variable width bitmaps */

	s16	nbitmaps;	/* Total number of bitmaps	*/
	s16	ndisplist;	/* Total number of display-list words */

	s16	bmheight;	/* Bitmap Texel height (Used)	*/
	s16	bmHreal;	/* Bitmap Texel height (Real)	*/
	bmformat	bmfmt;		/* Bitmap Format	 	*/
	bmtxsize	bmsiz;		/* Bitmap Texel Size		*/

	relocPointer bitmap;	/* Pointer to first bitmap	*/

	u32 rsp_dl;	/* Pointer to RSP display list	*/

	u32 rsp_dl_next;	/* Pointer to next RSP display entry	*/

	s16	frac_s,		/* Fractional Texture offsets */
		frac_t;		/* These have 5 fraction bits */
};

#define DL_BM_OVERHEAD (12)
#define DL_SPRITE_OVERHEAD (24)
#define NUM_DL(nb)      ((nb)*DL_BM_OVERHEAD +DL_SPRITE_OVERHEAD)
#define SP_TRANSPARENT	0x00000001
#define SP_CUTOUT		0x00000002
#define SP_HIDDEN		0x00000004
#define SP_Z			0x00000008
#define SP_SCALE		0x00000010
#define SP_FASTCOPY		0x00000020
#define SP_OVERLAP		0x00000040
#define SP_TEXSHIFT		0x00000080
#define SP_FRACPOS		0x00000100
#define SP_TEXSHUF		0x00000200
#define SP_EXTERN		0x00000400
#define SP_ARGUMENT		0x00000800
#define SP_CLOUD		0x00001000