/* farbfeld lib for creating images */

/* farbfeld header is:
 * 8 bytes: magic value == "farbfeld"
 * 4 bytes: width == uint32_t big-endian
 * 4 bytes: height == uint32_t big-endian
 * -------
 * 16 bytes total
 * farbfeld pixels are sRGB + alpha 
 * using uint16_t big-endian:
 * 2 bytes: Red
 * 2 bytes: Green
 * 2 bytes: Blue
 * 2 bytes: Alpha
 * -------
 * 8 bytes total
 */

#define FF_HEADER_SIZE 16
#define FF_PIXEL_SIZE 8

/* Pixel type for building the pixmap */
typedef struct Pixel_s {
	/* RGB + Alpha */
	uint16_t R, G, B, A;
} Pixel;

/* Picture type */
typedef struct FarbFeld_s {
	uint32_t width;
	uint32_t height;
	Pixel **pixmap;
} FarbFeld;


/* constructor */
FarbFeld* FF_init(uint32_t width, uint32_t height);

/* write picture to stdout */
int FF_write(const FarbFeld *picture);

/* takes an array of positions and plots it in the pixmap */
Pixel** FF_plot_pos(FarbFeld *picture, Point *positions, int npos);

/* 'private' functions */
Pixel** build_pixmap(FarbFeld *picture);
uint8_t* serial_header(const FarbFeld *picture);
uint8_t* serial_pixmap(const FarbFeld *picture);
