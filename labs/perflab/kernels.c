/********************************************************
 * Kernels to be optimized for the CS:APP Performance Lab
 ********************************************************/

#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Please fill in the following team struct
 */
team_t team = {
    "Potatoes", /* Team name */

    "Anderson Reyes",             /* First member full name */
    "reyesanderson428@gmail.com", /* First member email address */

    "", /* Second member full name (leave blank if none) */
    ""  /* Second member email addr (leave blank if none) */
};

/***************
 * ROTATE KERNEL
 ***************/

/******************************************************
 * Your different versions of the rotate kernel go here
 ******************************************************/

/*
 * naive_rotate - The naive baseline version of rotate
 */
char naive_rotate_descr[] = "naive_rotate: Naive baseline implementation";
void naive_rotate(int dim, pixel *src, pixel *dst) {
  int i, j;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(dim - 1 - j, i, dim)] = src[RIDX(i, j, dim)];
}

/*
 *  rotate V2 using loop unrolling
 */
char rotate_v2_descr[] = "rotate V2 loop unrolling";
void rotate_v2(int dim, pixel *src, pixel *dst) {
  int K = dim - 1;
  int i, ii, j, jj;

  int blocksize = 16;

  for (i = 0; i < dim; i += blocksize) {
    for (j = 0; j < dim; j += blocksize) {
      for (ii = i; ii < i + blocksize; ii++) {
        for (jj = j; jj < j + blocksize; jj++) {
          dst[RIDX(K - jj, ii, dim)] = src[RIDX(ii, jj, dim)];
        }
      }
    }
  }
}
/*
 * rotate - Your current working version of rotate
 * IMPORTANT: This is the version you will be graded on
 */
char rotate_descr[] = "rotate: Current working version";
void rotate(int dim, pixel *src, pixel *dst) { naive_rotate(dim, src, dst); }

/*********************************************************************
 * register_rotate_functions - Register all of your different versions
 *     of the rotate kernel with the driver by calling the
 *     add_rotate_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_rotate_functions() {
  add_rotate_function(&naive_rotate, naive_rotate_descr);
  add_rotate_function(&rotate, rotate_descr);
  add_rotate_function(&rotate_v2, rotate_v2_descr);
  /* ... Register additional test functions here */
}

/***************
 * SMOOTH KERNEL
 **************/

/***************************************************************
 * Various typedefs and helper functions for the smooth function
 * You may modify these any way you like.
 **************************************************************/

/* A struct used to compute averaged pixel value */
typedef struct {
  int red;
  int green;
  int blue;
  int num;
} pixel_sum;

/* Compute min and max of two integers, respectively */
static int min(int a, int b) { return (a < b ? a : b); }
static int max(int a, int b) { return (a > b ? a : b); }

/*
 * initialize_pixel_sum - Initializes all fields of sum to 0
 */
static void initialize_pixel_sum(pixel_sum *sum) {
  sum->red = sum->green = sum->blue = 0;
  sum->num = 0;
  return;
}

/*
 * accumulate_sum - Accumulates field values of p in corresponding
 * fields of sum
 */
static void accumulate_sum(pixel_sum *sum, pixel p) {
  sum->red += (int)p.red;
  sum->green += (int)p.green;
  sum->blue += (int)p.blue;
  sum->num++;
  return;
}

/*
 * assign_sum_to_pixel - Computes averaged pixel value in current_pixel
 */
static void assign_sum_to_pixel(pixel *current_pixel, pixel_sum sum) {
  current_pixel->red = (unsigned short)(sum.red / sum.num);
  current_pixel->green = (unsigned short)(sum.green / sum.num);
  current_pixel->blue = (unsigned short)(sum.blue / sum.num);
  return;
}

/*
 * avg - Returns averaged pixel value at (i,j)
 */
static pixel avg(int dim, int i, int j, pixel *src) {
  int ii, jj;
  pixel_sum sum;
  pixel current_pixel;

  initialize_pixel_sum(&sum);
  for (ii = max(i - 1, 0); ii <= min(i + 1, dim - 1); ii++)
    for (jj = max(j - 1, 0); jj <= min(j + 1, dim - 1); jj++)
      accumulate_sum(&sum, src[RIDX(ii, jj, dim)]);

  assign_sum_to_pixel(&current_pixel, sum);
  return current_pixel;
}

/******************************************************
 * Your different versions of the smooth kernel go here
 ******************************************************/

/*
 * naive_smooth - The naive baseline version of smooth
 */
char naive_smooth_descr[] = "naive_smooth: Naive baseline implementation";
void naive_smooth(int dim, pixel *src, pixel *dst) {
  int i, j;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++)
      dst[RIDX(i, j, dim)] = avg(dim, i, j, src);
}

/*
 * smooth v2
 */
char smooth_v2_descr[] = "smooth v2";
void smooth_v2(int dim, pixel *src, pixel *dst) {
  int K = dim - 1;
  int i, j;
  int ii, jj;

  for (i = 0; i < dim; i++)
    for (j = 0; j < dim; j++) {

      pixel *current_pixel = &dst[RIDX(i, j, dim)];
      current_pixel->red = current_pixel->green = current_pixel->blue = 0;
      int red = 0;
      int green = 0;
      int blue = 0;
      int num = 0;

      int max_i = max(i - 1, 0);
      int min_i = min(i + 1, K);
      int max_j = max(j - 1, 0);
      int min_j = min(j + 1, K);

      for (ii = max_i; ii <= min_i; ii++)
        for (jj = max_j; jj <= min_j; jj++) {
          pixel *src_pixel = &src[RIDX(ii, jj, dim)];
          red += (int)src_pixel->red;
          green += (int)src_pixel->green;
          blue += (int)src_pixel->blue;
          num++;
        }

      current_pixel->red = (unsigned short)(red / num);
      current_pixel->green = (unsigned short)(green / num);
      current_pixel->blue = (unsigned short)(blue / num);
    }
}

/*
 * smooth - Your current working version of smooth.
 * IMPORTANT: This is the version you will be graded on
 */
char smooth_descr[] = "smooth: Current working version";
void smooth(int dim, pixel *src, pixel *dst) { naive_smooth(dim, src, dst); }

/*********************************************************************
 * register_smooth_functions - Register all of your different versions
 *     of the smooth kernel with the driver by calling the
 *     add_smooth_function() for each test function.  When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_smooth_functions() {
  add_smooth_function(&smooth, smooth_descr);
  add_smooth_function(&naive_smooth, naive_smooth_descr);
  add_smooth_function(&smooth_v2, smooth_v2_descr);
  /* ... Register additional test functions here */
}
