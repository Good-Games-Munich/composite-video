#include "fabgl.h"
#include "logo.h"

#include <math.h>

#define VIDEOOUT_GPIO GPIO_NUM_25

fabgl::CVBS16Controller DisplayController;

// defaults
#define MODES_DEFAULT 0 // P-PAL-B
#define MONO_DEFAULT 0  // color
#define HRATE_DEFAULT 1 // horizontal rate (1 = x1, 2 = x2, 3 = x3)

// modes
static const char *MODES_STD[] = {
    "I-PAL-B",
    "P-PAL-B",
    "I-NTSC-M",
    "P-NTSC-M",
    "I-PAL-B-WIDE",
    "P-PAL-B-WIDE",
    "I-NTSC-M-WIDE",
    "P-NTSC-M-WIDE",
    "P-NTSC-M-EXT",
};

Bitmap bitmap1 = Bitmap(logo::xres, logo::yres, logo::data, PixelFormat::Mask, RGB888(255, 255, 255));

Sprite sprites[1];

void setup()
{
  DisplayController.begin(VIDEOOUT_GPIO);

  auto mode = MODES_DEFAULT;

  DisplayController.setHorizontalRate(HRATE_DEFAULT);
  DisplayController.setMonochrome(MONO_DEFAULT);

  DisplayController.setResolution(MODES_STD[mode]);

  // draw background
  Canvas cv(&DisplayController);
  cv.setBrushColor(RGB888(0, 0, 0));
  cv.clear();

  // Display resolution info
  // 640x480

  // adjust this to center screen in your monitor
  // DisplayController.moveScreen(-6, 0);

  // associates bitmaps to sprites
  sprites[0].addBitmap(&bitmap1);

  // sets initial position
  sprites[0].moveTo((DisplayController.getViewPortWidth() - logo::xres) / 2, (DisplayController.getViewPortHeight() - logo::yres) / 2);

  // makes sprites visible
  sprites[0].visible = true;

  // add sprites to display controller
  DisplayController.setSprites(sprites, 1);
  DisplayController.refreshSprites();
}

void loop()
{
}