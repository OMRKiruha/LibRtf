#ifndef __VXCOMMONLIB_LIBRTF_TEXT_H__
#define __VXCOMMONLIB_LIBRTF_TEXT_H__

#include <iostream>
#include <ostream>
#include <string>
#include "librtfcpp.h"

using namespace std;
using namespace format;

namespace RtfReader {
    class text :
            public format::processor,
            public format::utils::attributes_stack,
            public format::utils::fonts_stack {
    protected:
        ostream &stream;

    public:
        text(ostream &stream)
                : stream(stream) {
        }

        // format::processor
        void begin() override;

        void end() override;

        void title(const string &title) override;

        void keywords(const string &keywords) override;

        void author(const string &author) override;

        void summary(summary_categories cat, int param) override;

        void print(const string &) override;

        void print_symbol(const string &) override;

        void print_forced_space() override;

        int print_unicode(int) override;

        void hyperlink(const string &) override;

        void hyperlink_base(const string &) override;

        void print_char(special_characters ch) override;

        void font_smaller_begin() override;

        void font_smaller_end() override;

        void table_begin() override;

        void table_end() override;

        void table_cell_begin() override;

        void table_cell_end() override;

        void table_row_begin() override;

        void table_row_end() override;

        format::image_mgr *image_begin(const format::image_descr &image) override;

        void image_end(format::image_mgr &) override;


        // format::utils::attributes_stack
        void enable_attr(int attr, int param, bool enable) override;

        void attr_push(int attr, int param) override;

        void attrstack_push() override;

        void attrstack_drop() override;

        int attr_pop(int) override;

        void attr_drop_all() override;

        void attr_pop_all() override;

        void attr_pop_dump() override;

        void attr_remove(int *tab, int size) override;

        void attr_push_style(style::types type, int id) override;

        void register_style(const style &style) override;


        // format::utils::fonts_stack
        void register_font(int num, const char *fontname, int charset) override;

        // format::colors
        void register_color(uchar r, uchar g, uchar b) override;
    };
}
#endif