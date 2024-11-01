#include <stdio.h>
#include <assert.h>
#include <fstream>
#include <vector>

#define ARRAY_COUNT(x) (sizeof(x)/sizeof(x[0]))

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include "sp.h"

u32 FILE_013_XBOX_IMAGE_OFFSET = 0x2B8;
u32 FILE_013_WHITE_SQUARE = 0x6F0;
u32 FILE_013_PORTRAIT_QUESTION_MARK_IMAGE_OFFSET = 0xF68;
u32 FILE_013_BLACK_SQUARE = 0x13d0;
u32 FILE_013_PORTRAIT_FIRE_BG_IMAGE_OFFSET = 0x24D0;
u32 FILE_013_MARIO_OFFSET = 0x4728;
u32 FILE_013_LUIGI_OFFSET = 0x6978;
u32 FILE_013_DONKEY_OFFSET = 0x8bc8;
u32 FILE_013_SAMUS_OFFSET = 0xae18;
u32 FILE_013_FOX_OFFSET = 0xd068;
u32 FILE_013_KIRBY_OFFSET = 0xf2b8;
u32 FILE_013_LINK_OFFSET = 0x11508;
u32 FILE_013_YOSHI_OFFSET = 0x13758;
u32 FILE_013_PIKACHU_OFFSET = 0x159a8;
u32 FILE_013_NESS_OFFSET = 0x17bf8;
u32 FILE_013_CAPTAIN_OFFSET = 0x19e48;
u32 FILE_013_JIGGLYPUFF_OFFSET = 0x1c098;
u32 FILE_013_CAPTAIN_SHADOW_OFFSET = 0x1e2e8;
u32 FILE_013_LUIGI_SHADOW_OFFSET = 0x20538;
u32 FILE_013_NESS_SHADOW_OFFSET = 0x22788;
u32 FILE_013_JIGGLYPUFF_SHADOW_OFFSET = 0x249d8;

u32 FILE_30_PEACHS_CASTLE_TEXT = 0x1f8;
u32 FILE_30_SECTOR_Z_TEXT = 0x438;
u32 FILE_30_CONGO_JUNGLE_TEXT = 0x678;
u32 FILE_30_PLANET_ZEBES_TEXT = 0x8b8;
u32 FILE_30_HYRULE_CASTLE_TEXT = 0xb10;
u32 FILE_30_YOSHIS_ISLAND_TEXT = 0xd58;
u32 FILE_30_SAFFRON_CITY_TEXT = 0xf98;
u32 FILE_30_MUSHROOM_KINGDOM_TEXT = 0x11d8;
u32 FILE_30_DREAM_LAND_TEXT = 0x1418;
u32 FILE_30_CURSOR = 0x1ab8;
u32 FILE_30_QUESTION_MARK = 0x1dd8;
u32 FILE_30_STAGE_SELECT_TEXT = 0x26a0;
u32 FILE_30_WOODEN_CIRCLE = 0x3840;
u32 FILE_30_PLATE_RIGHT = 0x3c68;
u32 FILE_30_PLATE_MIDDLE = 0x3d68;
u32 FILE_30_PLATE_LEFT = 0x3fa8;
u32 FILE_30_PEACHS_CASTLE = 0x4d88;
u32 FILE_30_SECTOR_Z = 0x5b68;
u32 FILE_30_CONGO_JUNGLE = 0x6948;
u32 FILE_30_PLANET_ZEBES = 0x7728;
u32 FILE_30_HYRULE_CASTLE = 0x8508;
u32 FILE_30_YOSHIS_ISLAND = 0x92e8;
u32 FILE_30_SAFFRON_CITY = 0xa0c8;
u32 FILE_30_MUSHROOM_KINGDOM = 0xaea8;
u32 FILE_30_DREAM_LAND = 0xbc88;
u32 FILE_30_TILES = 0xc728;
u32 FILE_30_RANDOM_SMALL = 0xcb10;
u32 FILE_30_RANDOM_BIG = 0xde30;

u32 FILE_38_1P = 0x258;
u32 FILE_38_2P = 0x4f8;
u32 FILE_38_3P = 0x798;
u32 FILE_38_4P = 0xa38;
u32 FILE_38_CP = 0xcd8;
u32 FILE_38_ALLY = 0xeb8;

void changeEndianness(u8* c, u32 n)
{
	static std::vector<u8> temp;
	temp.resize(n);
	for (int i = 0; i < n; temp[i] = c[i], i++);
	for (int i = 0; i < n; c[i] = temp[n - 1 - i], i++);
}

void fixSpriteEndianness(Sprite* sprite)
{
	changeEndianness((u8*)&sprite->x, 2);
	changeEndianness((u8*)&sprite->y, 2);
	changeEndianness((u8*)&sprite->width, 2);
	changeEndianness((u8*)&sprite->height, 2);
	changeEndianness((u8*)&sprite->scalex, 4);
	changeEndianness((u8*)&sprite->scaley, 4);
	changeEndianness((u8*)&sprite->expx, 2);
	changeEndianness((u8*)&sprite->expy, 2);
	changeEndianness((u8*)&sprite->attr, 2);
	changeEndianness((u8*)&sprite->zdepth, 2);
	changeEndianness((u8*)&sprite->startTLUT, 2);
	changeEndianness((u8*)&sprite->nTLUT, 2);
	changeEndianness((u8*)&sprite->LUT.nextPointer, 2);
	changeEndianness((u8*)&sprite->LUT.pointer, 2);
	changeEndianness((u8*)&sprite->istart, 2);
	changeEndianness((u8*)&sprite->istep, 2);
	changeEndianness((u8*)&sprite->nbitmaps, 2);
	changeEndianness((u8*)&sprite->ndisplist, 2);
	changeEndianness((u8*)&sprite->bmheight, 2);
	changeEndianness((u8*)&sprite->bmHreal, 2);
	changeEndianness((u8*)&sprite->bitmap.nextPointer, 2);
	changeEndianness((u8*)&sprite->bitmap.pointer, 2);
	changeEndianness((u8*)&sprite->rsp_dl, 4);
	changeEndianness((u8*)&sprite->rsp_dl_next, 4);
	changeEndianness((u8*)&sprite->frac_s, 2);
	changeEndianness((u8*)&sprite->frac_t, 2);
}

void fixBitmapEndianness(Bitmap* bitmap, int count = 1)
{
	for (int i = 0; i < count; i++)
	{
		changeEndianness((u8*)&bitmap[i].width, 2);
		changeEndianness((u8*)&bitmap[i].width_img, 2);
		changeEndianness((u8*)&bitmap[i].s, 2);
		changeEndianness((u8*)&bitmap[i].t, 2);
		changeEndianness((u8*)&bitmap[i].buf.nextPointer, 2);
		changeEndianness((u8*)&bitmap[i].buf.pointer, 2);
		changeEndianness((u8*)&bitmap[i].actualHeight, 2);
		changeEndianness((u8*)&bitmap[i].LUToffset, 2);
	}
}

u32 spriteGetBpp(Sprite* sprite)
{
	switch (sprite->bmsiz)
	{
	case G_IM_SIZ_4b:
		return 4U;
	case G_IM_SIZ_8b:
		return 8U;
	case G_IM_SIZ_16b:
		return 16U;
	case G_IM_SIZ_32b:
		return 32U;
	default:
		return ~0U;
	}
}

void spritePrint(Sprite* sprite)
{
	printf("Sprite 0x%llx:\n", (unsigned long long)sprite);
	printf("   x, y:           %d, %d\n", sprite->x, sprite->y);
	printf("   width, height:  %d, %d\n", sprite->width, sprite->height);
	printf("   scalex, scaley: %d, %d\n", sprite->scalex, sprite->scaley);
	printf("   expx, expy:     %d, %d\n", sprite->expx, sprite->expy);
	printf("   attr:           0x%x\n", sprite->attr);
	printf("   zdepth:         %d\n", sprite->zdepth);
	printf("   r, g, b, a:     0x%x, 0x%x, 0x%x, 0x%x\n", sprite->red, sprite->green, sprite->blue, sprite->alpha);
	printf("   startTLUT:      %d\n", sprite->startTLUT);
	printf("   nTLUT:          %d\n", sprite->nTLUT);
	printf("   istart:         %d\n", sprite->istart);
	printf("   istep:          %d\n", sprite->istep);
	printf("   nbitmaps:       %d\n", sprite->nbitmaps);
	printf("   ndisplist:      %d\n", sprite->ndisplist);
	printf("   bmheight:       %d\n", sprite->bmheight);
	printf("   bmHreal:        %d\n", sprite->bmHreal);
	switch (sprite->bmfmt)
	{
	case G_IM_FMT_RGBA:
		printf("   bmfmt:          RGBA\n");
		break;
	case G_IM_FMT_YUV:
		printf("   bmfmt:          YUV\n");
		break;
	case G_IM_FMT_CI:
		printf("   bmfmt:          CI\n");
		break;
	case G_IM_FMT_IA:
		printf("   bmfmt:          IA\n");
		break;
	case G_IM_FMT_I:
		printf("   bmfmt:          I\n");
		break;
	}
	switch (sprite->bmsiz)
	{
	case G_IM_SIZ_4b:
		printf("   bmsiz:          4b\n");
		break;
	case G_IM_SIZ_8b:
		printf("   bmsiz:          8b\n");
		break;
	case G_IM_SIZ_16b:
		printf("   bmsiz:          16b\n");
		break;
	case G_IM_SIZ_32b:
		printf("   bmsiz:          32b\n");
		break;
	case G_IM_SIZ_4c:
		printf("   bmsiz:          4c\n");
		break;
	case G_IM_SIZ_DD:
		printf("   bmsiz:          DD\n");
		break;
	}
	printf("   LUT.nextPointer: 0x%x\n", sprite->LUT.nextPointer);
	printf("   LUT.pointer:     0x%x (0x%x = %d)\n", sprite->LUT.pointer, sprite->LUT.pointer * 4, sprite->LUT.pointer * 4);
	printf("   bitmap.nextPointer: 0x%x\n", sprite->bitmap.nextPointer);
	printf("   bitmap.pointer:     0x%x (0x%x = %d)\n", sprite->bitmap.pointer, sprite->bitmap.pointer * 4, sprite->bitmap.pointer * 4);
}

bool spriteNeedsWordSwap(Sprite* sprite)
{
	return sprite->bmsiz < G_IM_SIZ_4c;
}

void bitmapPrint(Bitmap* bitmap)
{
	printf("Bitmap 0x%llx:\n", (unsigned long long)bitmap);
	printf("   width:        %d\n", bitmap->width);
	printf("   width_img:    %d\n", bitmap->width_img);
	printf("   s:            %d\n", bitmap->s);
	printf("   t:            %d\n", bitmap->t);
	printf("   actualHeight: %d\n", bitmap->actualHeight);
	printf("   LUToffset:    %d\n", bitmap->LUToffset);
	printf("   buf.nextPointer: 0x%x\n", bitmap->buf.nextPointer);
	printf("   buf.pointer:     0x%x (0x%x = %d)\n\n", bitmap->buf.pointer, bitmap->buf.pointer * 4, bitmap->buf.pointer * 4);
}


void printBits(size_t const size, void const* const ptr)
{
	unsigned char* b = (unsigned char*)ptr;
	unsigned char byte;
	int i, j;

	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
	puts("");
}

void imgWordSwap(u32 height, u32 width, u32 bpp, u8* dv)
{
	u32 baseOffset;

	//put width in terms of bytes instead of pixels
	width = width * bpp / 8;

	switch (bpp) {

	case 32:
	{
		u32 a1, a2, b1, b2;

		for (u32 y = 1; y < height; y += 2) {
			for (u32 x = 0; x < width; x += 16) {
				baseOffset = x + width * y;

				a1 = *((u32*)&dv[baseOffset + 0]);
				a2 = *((u32*)&dv[baseOffset + 4]);
				b1 = *((u32*)&dv[baseOffset + 8]);
				b2 = *((u32*)&dv[baseOffset + 12]);

				*((u32*)&dv[baseOffset + 0]) = b1;
				*((u32*)&dv[baseOffset + 4]) = b2;
				*((u32*)&dv[baseOffset + 8]) = a1;
				*((u32*)&dv[baseOffset + 12]) = a2;
			}
		}
		break;
	}
	default:
	{
		//every image in SSB64 is probably padded to be even, but for custom images... 
		const u32 Even_Width = ((width / 4) % 2) == 1 ? width - 4 : width;

		u32 a, b;

		for (u32 y = 1; y < height; y += 2) {
			for (u32 x = 0; x < Even_Width; x += 8) {
				baseOffset = x + width * y;

				a = *((u32*)&dv[baseOffset + 0]);
				b = *((u32*)&dv[baseOffset + 4]);
				*((u32*)&dv[baseOffset + 0]) = b;
				*((u32*)&dv[baseOffset + 4]) = a;
			}
		}
		break;
	}
	}
}


void* SampleColorIndex(u32 y, u32 x, u8* bitmapBuffer, u32 widthInPixels, u32 bitsPerPixel, u8* outCI)
{
	switch (bitsPerPixel)
	{
	case 4:
	{
		u32 offsetInPixels = widthInPixels * y + x;
		u32 targetByte = offsetInPixels / 2;
		if (offsetInPixels % 2 == 0)
			*outCI = ((bitmapBuffer[targetByte] & 0xf0) >> 4);
		else
			*outCI = (bitmapBuffer[targetByte] & 0x0f);
		return &bitmapBuffer[targetByte];
	}
	case 8:
	{
		u32 targetByte = widthInPixels * y + x;
		*outCI = bitmapBuffer[targetByte];
		return &bitmapBuffer[targetByte];
	}
	default:
		assert(false);
	}
}

void* SampleGrayscale(u32 y, u32 x, u8* bitmapBuffer, u32 widthInPixels, u32 bitsPerPixel, u8* outI)
{
	switch (bitsPerPixel)
	{
	case 4:
	{
		u32 offsetInPixels = widthInPixels * y + x;
		u32 targetByte = offsetInPixels / 2;
		if (offsetInPixels % 2 == 0)
			*outI = ((bitmapBuffer[targetByte] & 0xf0) >> 4);
		else
			*outI = (bitmapBuffer[targetByte] & 0x0f);
		*outI = (*outI) | ((*outI) << 4);
		return &bitmapBuffer[targetByte];
	}
	case 8:
	{
		u32 targetByte = widthInPixels * y + x;
		*outI = bitmapBuffer[targetByte];
		return &bitmapBuffer[targetByte];
	}
	default:
		assert(false);
	}
}

void* SampleGrayscaleAlpha(u32 y, u32 x, u8* bitmapBuffer, u32 widthInPixels, u32 bitsPerPixel, u8* outI, u8* outA)
{
	switch (bitsPerPixel)
	{
	case 4:
	{
		u32 offsetInPixels = widthInPixels * y + x;
		u32 targetByte = offsetInPixels / 2;
		if (offsetInPixels % 2 == 0)
		{
			*outI = ((bitmapBuffer[targetByte] & 0xe0));
			*outA = ((bitmapBuffer[targetByte] & 0x10) >> 4);
		}
		else
		{
			*outI = ((bitmapBuffer[targetByte] & 0x0e) << 4);
			*outA = ((bitmapBuffer[targetByte] & 0x01));
		}
		*outI = (*outI) | ((*outI) >> 3) | ((*outI) >> 6);
		*outA *= 255;

		return &bitmapBuffer[targetByte];
	}
	case 8:
	{
		u32 targetByte = widthInPixels * y + x;
		u8 byte = bitmapBuffer[targetByte];
		*outI = ((byte & 0xf0) >> 4);
		*outA = ((byte & 0x0f));
		*outI = (*outI) | ((*outI) << 4);
		*outA = (*outA) | ((*outA) << 4);
		return &bitmapBuffer[targetByte];
	}
	default:
		assert(false);
	}
}

void* SampleRgba(u32 y, u32 x, u8* bitmapBuffer, u32 widthInPixels, u32 bitsPerPixel, u8* outR, u8* outG, u8* outB, u8* outA)
{
	switch (bitsPerPixel)
	{
	case 32:
	{
		u32 targetByte = (widthInPixels * y + x) * 4;
		*outR = bitmapBuffer[targetByte + 0];
		*outG = bitmapBuffer[targetByte + 1];
		*outB = bitmapBuffer[targetByte + 2];
		*outA = bitmapBuffer[targetByte + 3];
		return &bitmapBuffer[targetByte];
	}
	case 16:
	{
		u32 targetByte = (widthInPixels * y + x) * 2;
		u16 hword = *((u16*)&bitmapBuffer[targetByte]);
		hword = (hword << 8) | (hword >> 8); // endianness
		*outR = ((hword & 0xf800) >> 11);
		*outG = ((hword & 0x07c0) >> 6);
		*outB = ((hword & 0x003e) >> 1);
		*outA = (hword & 0x0001) * 255;
		*outR = ((*outR) << 3) | ((*outR) >> 2);
		*outG = ((*outG) << 3) | ((*outG) >> 2);
		*outB = ((*outB) << 3) | ((*outB) >> 2);
		return &bitmapBuffer[targetByte];
	}
	default:
		assert(false);
	}
}

void SpriteToPng(Sprite* sprite, Bitmap* bitmaps, const std::vector<u8*>& bitmapBuffers, u8* palette, const char* outputFilePath)
{
	u32 targetWidth = sprite->width;
	u32 targetHeight = sprite->height;
	u32 bitsPerPixel = spriteGetBpp(sprite);
	assert(bitsPerPixel != ~0U);

	u32 actualHeightSum = 0;
	for (u32 i = 0; i < sprite->nbitmaps; i++)
		actualHeightSum += bitmaps[i].actualHeight;
	bool needToSubtract = sprite->height < actualHeightSum;

	std::vector<u8> pngBuffer;
	pngBuffer.resize(targetWidth * targetHeight * 4);

	u32 writtenRows = 0;
	for (u32 i = 0; i < sprite->nbitmaps; i++)
	{
		u32 widthWithPadding = bitmaps[i].width_img;
		u32 currentBitmapHeight = bitmaps[i].actualHeight;

		if (spriteNeedsWordSwap(sprite))
			imgWordSwap(currentBitmapHeight, widthWithPadding, bitsPerPixel, bitmapBuffers[i]);

		if (sprite->bmfmt == G_IM_FMT_CI)
			imgWordSwap(1, bitsPerPixel == 4 ? 16 : 256, bitsPerPixel, palette);

		for (size_t y = 0; y < currentBitmapHeight && writtenRows < targetHeight; y++, writtenRows++)
		{
			for (size_t x = 0; x < targetWidth; x++)
			{
				switch (sprite->bmfmt)
				{
				case G_IM_FMT_I:
				{
					u8 grayscaleValue;
					void* sampledByte = SampleGrayscale(y, x, bitmapBuffers[i], widthWithPadding, bitsPerPixel, &grayscaleValue);
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 0] = grayscaleValue;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 1] = grayscaleValue;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 2] = grayscaleValue;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 3] = 255;
					break;
				}
				case G_IM_FMT_IA:
				{
					u8 grayscaleValue, alpha;
					void* sampledByte = SampleGrayscaleAlpha(y, x, bitmapBuffers[i], widthWithPadding, bitsPerPixel, &grayscaleValue, &alpha);
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 0] = grayscaleValue;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 1] = grayscaleValue;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 2] = grayscaleValue;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 3] = alpha;
					break;
				}
				case G_IM_FMT_RGBA:
				{
					u8 r, g, b, a;
					void* sampledByte = SampleRgba(y, x, bitmapBuffers[i], widthWithPadding, bitsPerPixel, &r, &g, &b, &a);
					//printf("sampled byte: %p\n", sampledByte);
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 0] = r;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 1] = g;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 2] = b;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 3] = a;
					break;
				}
				case G_IM_FMT_CI:
				{
					u8 colorIndex, r, g, b, a;
					void* sampledByte = SampleColorIndex(y, x, bitmapBuffers[i], widthWithPadding, bitsPerPixel, &colorIndex);
					SampleRgba(0, colorIndex, palette, 0, 16, &r, &g, &b, &a);
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 0] = r;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 1] = g;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 2] = b;
					pngBuffer[writtenRows * 4 * targetWidth + x * 4 + 3] = a;
					break;
				}
				default:
					assert(false);
				}
			}
		}
		if (needToSubtract)
			writtenRows--;
	}

	stbi_write_png(outputFilePath, targetWidth, targetHeight, 4, pngBuffer.data(), targetWidth * 4);
}


int main()
{
	assert(sizeof(short) == 2);
	assert(sizeof(unsigned long) == 4);

	struct PerFileInfo {
		u32 fileId;
		const char* relocFilePath;
		u32* offsets;
		u32 offsetCount;
	};
	PerFileInfo perFileInfo[] = {
		{ 19, "files/19.vpk0.bin", &FILE_013_XBOX_IMAGE_OFFSET, 21 },
		{ 30, "files/30.vpk0.bin", &FILE_30_PEACHS_CASTLE_TEXT, 28 },
		{ 38, "files/38.vpk0.bin", &FILE_38_1P, 6 },
	};

	
	for (u32 currentFile = 0; currentFile < ARRAY_COUNT(perFileInfo); currentFile++)
	{
		std::ifstream file(perFileInfo[currentFile].relocFilePath, std::ios::binary | std::ios::ate);
		if (!file.is_open())
		{
			printf("File not found: %s\n", perFileInfo[currentFile].relocFilePath);
			exit(-1);
		}

		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);
		std::vector<u8> buffer(size);
		if (!file.read((char*)buffer.data(), size))
			exit(1);

		u32* currentOffset = perFileInfo[currentFile].offsets;
		for (u32 i = 0; i < perFileInfo[currentFile].offsetCount; i++, currentOffset++)
		{
			u32 targetOffset = *currentOffset;
			printf("targetOffset: 0x%x = %d\n", targetOffset, targetOffset);
			Sprite* sprite = (Sprite*)((u64)buffer.data() + targetOffset);
			fixSpriteEndianness(sprite);
			spritePrint(sprite);
			Bitmap* bitmaps = (Bitmap*)((u64)buffer.data() + (sprite->bitmap.pointer * 4));
			fixBitmapEndianness(bitmaps, sprite->nbitmaps);
			for (int i = 0; i < sprite->nbitmaps; i++)
				bitmapPrint(&bitmaps[i]);
			std::vector<u8*> bitmapBuffers;
			bitmapBuffers.resize(sprite->nbitmaps);
			for (int i = 0; i < sprite->nbitmaps; i++)
				bitmapBuffers[i] = (u8*)((u64)buffer.data() + (bitmaps[i].buf.pointer * 4));
			u8* palette = NULL;
			if (sprite->nTLUT > 0)
			{
				palette = (u8*)((u64)buffer.data() + (sprite->LUT.pointer * 4));
			}

			char pngFilePath[64];
			sprintf_s(pngFilePath, "output_images/%u_%x.png", perFileInfo[currentFile].fileId, targetOffset);
			SpriteToPng(sprite, bitmaps, bitmapBuffers, palette, pngFilePath);
		}
	}
}
