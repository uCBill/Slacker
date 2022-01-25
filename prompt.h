// 'prompt', 7x14px
const unsigned char epd_bitmap_prompt [] PROGMEM = {
	0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe, 0xfe
};

// Array of all bitmaps for convenience. (Total bytes used to store images in PROGMEM = 32)
const int epd_bitmap_allArray_LEN = 1;
const unsigned char* epd_bitmap_allArray[1] = {
	epd_bitmap_prompt
};
