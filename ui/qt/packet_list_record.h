/* packet_list_record.h
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef PACKET_LIST_RECORD_H
#define PACKET_LIST_RECORD_H

#include "config.h"

#include <glib.h>

#include "cfile.h"

#include <epan/column-info.h>
#include <epan/packet.h>

#include <QByteArray>
#include <QList>
#include <QVariant>

class PacketListRecord
{
public:
    PacketListRecord(frame_data *frameData);
    // Return the string value for a column. Data is cached if possible.
    const QVariant columnString(capture_file *cap_file, int column);
    frame_data *frameData() const { return fdata_; }
    // packet_list->col_to_text in gtk/packet_list_store.c
    static int textColumn(int column) { return cinfo_column_.value(column, -1); }

    int columnTextSize(const char *str);
    static void resetColumns(column_info *cinfo);
    void resetColorized();

private:
    /** The column text for some columns */
    QList<QByteArray> col_text_;

    frame_data *fdata_;
    static QMap<int, int> cinfo_column_;


    /** Has this record been columnized? */
//    gboolean columnized_;
    /** Has this record been colorized? */
    bool colorized_;

    void dissect(capture_file *cap_file, bool dissect_color = false);
    void cacheColumnStrings(column_info *cinfo);

};

#endif // PACKET_LIST_RECORD_H

/*
 * Editor modelines
 *
 * Local Variables:
 * c-basic-offset: 4
 * tab-width: 8
 * indent-tabs-mode: nil
 * End:
 *
 * ex: set shiftwidth=4 tabstop=8 expandtab:
 * :indentSize=4:tabSize=8:noTabs=true:
 */
