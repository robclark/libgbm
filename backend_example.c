/*
 * Copyright (C) 2012 Texas Instruments
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT.  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Rob Clark <rob.clark@linaro.org>
 */

/* This is an example/skeletal backend implementation.. this file isn't
 * actually built as part of libgbm, but just intended to be a template
 * to help in creating a new gbm backend
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <limits.h>

#include <sys/types.h>
#include <unistd.h>
#include <dlfcn.h>

#include "gbmint.h"
#include "common_drm.h"

struct gbm_example_device {
   struct gbm_drm_device base;
   /* add whatever you need here */
};

struct gbm_example_bo {
   struct gbm_drm_bo base;
   /* add whatever you need here */
};


static int
gles_init(struct gbm_example_device *dev)
{
   /* this should open/initialize the GLES stack.. for a DRM driver
    * at least, dev->base.base.fd will have the already opened device
    */
   return 0;
}

static int
gbm_example_is_format_supported(struct gbm_device *gbm,
      enum gbm_bo_format format, uint32_t usage)
{
   return 0;
}

static void
gbm_example_bo_destroy(struct gbm_bo *_bo)
{
}

static struct gbm_bo *
gbm_example_bo_create_from_egl_image(struct gbm_device *gbm, void *egl_dpy,
      void *egl_img, uint32_t width, uint32_t height, uint32_t usage)
{
   /* eglimg is created w/  (see weston_buffer_attach()):
    *
    *   struct wl_buffer *buffer = ...;
    *   eglCreateImageKHR(display, NULL, EGL_WAYLAND_BUFFER_WL, buffer, NULL);
    */

   return NULL;
}

static struct gbm_bo *
gbm_example_bo_create(struct gbm_device *gbm, uint32_t width, uint32_t height,
      enum gbm_bo_format format, uint32_t usage)
{
   return NULL;
}

static void
gbm_example_destroy(struct gbm_device *gbm)
{
}

static struct gbm_device *
example_device_create(int fd)
{
   struct gbm_example_device *dev;
   int ret;

   dev = calloc(1, sizeof *dev);

   dev->base.base.fd = fd;
   dev->base.base.bo_create = gbm_example_bo_create;
   dev->base.base.bo_create_from_egl_image = gbm_example_bo_create_from_egl_image;
   dev->base.base.is_format_supported = gbm_example_is_format_supported;
   dev->base.base.bo_destroy = gbm_example_bo_destroy;
   dev->base.base.destroy = gbm_example_destroy;

   dev->base.type = GBM_DRM_DRIVER_TYPE_CUSTOM;
   dev->base.base.name = "example";

   ret = gles_init(dev);
   if (ret) {
      free(dev);
      return NULL;
   }

   return &dev->base.base;
}

/* backend loader looks for symbol "gbm_backend" */
struct gbm_backend gbm_backend = {
   .backend_name = "example",
   .create_device = example_device_create,
};
