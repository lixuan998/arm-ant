#pragma once
#include <lib/printk.h>

#define AA_LOGO         "    [[                                       [[                [[   \n\r"\
                        "   [[[[    [[[[[    [[[  [[[   [[   [[      [[[[     [[[[   [[[[[[[[\n\r"\
                        "  [[  [[  [[   [[ [[   [[   [[ [[   [[     [[  [[  [[    [[    [[   \n\r"\
                        " [[    [[ [[      [[   [[   [[ [[   [[    [[    [[ [[    [[    [[   \n\r"\
                        " [[[[[[[[ [[      [[   [[   [[ [[   [[    [[[[[[[[ [[    [[    [[   \n\r"\
                        " [[    [[ [[      [[   [[   [[ [[   [[    [[    [[ [[    [[    [[   \n\r"\
                        " [[    [[ [[      [[   [[   [[  [[[[[     [[    [[ [[    [[     [[[[\n\r"\
                        "                                  [[                                \n\r"\
                        "                                 [[                                 \n\r"\
                        "                              [[[[                   @Author: Lixuan\n\r"

static inline void print_logo(void)
{
    printk(AA_LOGO);
}
