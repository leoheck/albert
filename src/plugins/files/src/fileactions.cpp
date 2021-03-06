// albert - a simple application launcher for linux
// Copyright (C) 2014-2016 Manuel Schneider
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

#include "fileactions.h"

/******************************************************************************/

Files::FileAction::FileAction(Files::File *file) : file_(file) {

}

Files::FileAction::~FileAction() {

}

/******************************************************************************/

Files::File::OpenFileAction::OpenFileAction(Files::File *file) : FileAction(file) {

}

QString Files::File::OpenFileAction::text() const {
    return "Open with default application";
}

void Files::File::OpenFileAction::activate() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(file_->path()));
}

/******************************************************************************/

Files::File::RevealFileAction::RevealFileAction(Files::File *file) : FileAction(file) {

}

QString Files::File::RevealFileAction::text() const {
    return "Reveal in default file browser";
}

void Files::File::RevealFileAction::activate() {
    QDesktopServices::openUrl(QUrl::fromLocalFile(QFileInfo(file_->path()).path()));
}

/******************************************************************************/

Files::File::CopyFileAction::CopyFileAction(Files::File *file) : FileAction(file) {

}

QString Files::File::CopyFileAction::text() const {
    return "Copy to clipboard";
}

void Files::File::CopyFileAction::activate() {
    //  Get clipboard
    QClipboard *cb = QApplication::clipboard();

    // Ownership of the new data is transferred to the clipboard.
    QMimeData* newMimeData = new QMimeData();

    // Copy old mimedata
    const QMimeData* oldMimeData = cb->mimeData();
    for (const QString &f : oldMimeData->formats())
        newMimeData->setData(f, oldMimeData->data(f));

    // Copy path of file
    newMimeData->setText(file_->path());

    // Copy file
    newMimeData->setUrls({QUrl::fromLocalFile(file_->path())});

    // Copy file (f*** you gnome)
    QByteArray gnomeFormat = QByteArray("copy\n").append(QUrl::fromLocalFile(file_->path()).toEncoded());
    newMimeData->setData("x-special/gnome-copied-files", gnomeFormat);

    // Set the mimedata
    cb->setMimeData(newMimeData);
}

/******************************************************************************/

Files::File::CopyPathAction::CopyPathAction(Files::File *file) : FileAction(file) {

}

QString Files::File::CopyPathAction::text() const {
    return "Copy path to clipboard";
}

void Files::File::CopyPathAction::activate() {
    QApplication::clipboard()->setText(file_->path());
}
