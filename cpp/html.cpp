/***************************************************************************
 *   Copyright (C) 2006 by Tomasz Hławiczka                                *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU Library General Public License as       *
 *   published by the Free Software Foundation; either version 2 of the    *
 *   License, or (at your option) any later version.                       *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU Library General Public     *
 *   License along with this program; if not, write to the                 *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

//#include <iostream>
#include <ostream>
#include <string>

#include "librtfcpp.h"

using namespace std;
using namespace format;

class html :
        public format::processor,
        public format::utils::attributes_stack,
        public format::utils::fonts_stack {
protected:
    ostream &stream;
    std::string default_fontname, default_color;

protected:

    struct html_color {
        html_color(uchar r, uchar g, uchar b)
                : r(r), g(g), b(b) {
        }

        const std::string &html() {
            if (!cache.empty())
                return cache;

            char str[8];
            sprintf(str, "#%02x%02x%02x", r, g, b);
            cache = str;
            return cache;
        }

        uchar r, g, b;
        std::string cache;
    };

    std::vector<html_color> colors;
    bool in_body, in_head;

public:
    html(ostream &stream)
            : stream(stream),
              default_fontname("Helvetica"),
              default_color("#000000"),
              in_body(false),
              in_head(false) {
    }

    std::string htmlencode(const std::string &text) {
        return text;
    }

    const std::string &find_font(int param) {
        auto it = this->fonts.find(param);
        if (it == this->fonts.end()) {
            // error, needed font not found
            return default_fontname;
        }
        return it->second;
    }

    const std::string &find_color(int param) {
        if ((size_t) param >= colors.size())
            return default_color;
        return colors[param].html();
    }

    void register_color(uchar r, uchar g, uchar b) override {
        colors.push_back(html_color(r, g, b));
    }

    void enable_attr(int attr, int param, bool enable) override {
        start_body();
        switch (attr) {
            case none:
                break;
            case bold:
                stream << (enable ? "<b>" : "</b>");
                break;
            case italic:
                stream << (enable ? "<b>" : "</b>");
                break;

            case underline:
            case double_ul:
            case word_ul :
            case thick_ul:
            case wave_ul:
            case dot_ul:
            case dash_ul:
            case dot_dash_ul:
            case dbl_dot_dash_ul:
                stream << (enable ? "<b>" : "</b>");
                break;

            case fontsize:
                if (enable)
                    stream << "<font size='" << param << "'>";
                else
                    stream << "</font>";
                break;
            case std_fontsize:
                if (enable)
                    stream << "<font size='" << param << "'>";
                else
                    stream << "</font>";
                break;
            case fontface:
                if (enable)
                    stream << "<font face='" << find_font(param).c_str() << "'>";
                else
                    stream << "</font>";
                break;
            case foreground:
                if (enable)
                    stream << "<font color='" << find_color(param).c_str() << "'>";
                else
                    stream << "</font>";
                break;
            case background:
                stream << (enable ? "<span>" : "</span>");
                break;
            case caps:
                break;
            case smallcaps:
                break;

            case shadow:
            case outline:
            case emboss:
            case engrave:

            case super:
            case sub:
            case strike:
            case dbl_strike:
            case expand:
                break;
        }
    }

    void start_body() {
        if (in_body) return;
        if (in_head)
            stream << "</head>";
        stream << "<body>";
        in_body = true;

        attr_push_style(format::attributes::style::character, 0);
    }

    void begin() override {
        stream << "<html>";
        stream << "<head>";
        in_head = true;
    }

    void end() override {
        if (in_body)
            stream << "</body>";
        else if (in_head)
            stream << "</head>";

        stream << "</html>";
    }

    void title(const std::string &title) override {
        stream << "<title>" << htmlencode(title) << "</title>";
    }

    void font_smaller_begin() override {
        start_body();
        stream << "<small>";
    }

    void font_smaller_end() override {
        start_body();
        stream << "</small>";
    }

    void keywords(const std::string &text) override {
        stream << "<keywords>" << htmlencode(text) << "</keywords>";
    }

    void author(const std::string &text) override {
    }

    void print(const std::string &text) override {
        start_body();
        stream << text;
    }

    void print_symbol(const std::string &) override {
        start_body();
    }

    void print_forced_space() override {
        start_body();
        stream << "&nbsp;";
    }

    int print_unicode(int x) override {
        start_body();
        return 1;
    }

    void hyperlink_base(const std::string &url_base) override {
    }

    void hyperlink(const std::string &text) override {
        start_body();
        stream << "<a href='#'>" << htmlencode(text) << "</a>";
    }

    void print_char(special_characters spc) override {
        start_body();
        switch (spc) {
            case bullet:
            case left_quote:
                stream << "\"";
                break;
            case right_quote:
                stream << "\"";
                break;
            case left_dbl_quote:
                stream << "\"";
                break;
            case right_dbl_quote:
                stream << "\"";
                break;
            case nonbreaking_space:
                stream << "&nbsp;";
                break;
            case emdash:
                stream << "";
                break;
            case endash:
                stream << "";
                break;
            case lessthan:
                stream << "&lt;";
                break;
            case greaterthan:
                stream << "&gt;";
                break;
            case amp:
                stream << "&amp;";
                break;
            case copyright:
                stream << "&copy;";
                break;
            case trademark:
                stream << "&trade??;";
                break;
            case nonbreaking_hyphen:
                stream << "-";
                break;
            case optional_hyphen:
                stream << "-";
                break;
            case dbl_quote:
                stream << "\"";
                break;
            case line_break:
                stream << "<br>";
                break;
            case page_break:
                stream << "<br>";
                break;
            case paragraph_begin:
                stream << "<p>";
                break;
            case center_begin:
                stream << "<center>";
                break;
            case right_begin:
                stream << "";
                break;
            case justify_begin:
                stream << "";
                break;
            case center_end:
                stream << "";
                break;
            case right_end:
                stream << "";
                break;
            case justify_end:
                stream << "";
                break;
            case tab:
                stream << "\t";
                break;
            default :
                break;
        }
    }

    void table_begin() override {
        start_body();
        stream << "<table>";
    }

    void table_end() override {
        start_body();
        stream << "</table>";
    }

    void table_cell_begin() override {
        start_body();
        stream << "<td>";
    }

    void table_cell_end() override {
        start_body();
        stream << "</td>";
    }

    void table_row_begin() override {
        start_body();
        stream << "<tr>";
    }

    void table_row_end() override {
        start_body();
        stream << "</tr>";
    }

    virtual void image(const char *src) {
        start_body();
        stream << "<img src='" << src << "'>"; // FIXME : urlencode
    }

    image_mgr *image_begin(const image_descr &image) override {
        start_body();
        return new format::utils::file_image_mgr("/tmp/zzzzzzz.bmp");
    }

    void image_end(image_mgr &image) override {
        start_body();
        delete &image;
    }

    void summary(summary_categories cat, int param) override {
    }

};
/*
int main (int argc, const char ** argv) 
{
	using namespace std;

	if( argc == 1 )
	{
		cerr << "Usage: " << argv[0] << " <file.rtf>" << endl;
		return -1;
	}

	const char * filename = argv[1];

	try
	{
		cerr << "Starting converter " << endl;
		
		using namespace format;
		utils::stream_logger log ( cerr, true, true, true );

		ifstream file ( filename );
		utils::stream_source src ( file );
		
		
		html proc ( cout );
		
		parsers::rtf parser ( src, proc, log );
		
		cout << endl;
	}
	catch ( ... )
	{
		cerr << "Exception cateched" << endl;
	}

	return 0;
}
*/