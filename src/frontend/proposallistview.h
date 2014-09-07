// albert - a simple application launcher for linux
// Copyright (C) 2014 Manuel Schneider
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

#ifndef PROPOSALLISTVIEW_H
#define PROPOSALLISTVIEW_H

#include <QListWidget>
#include <QEvent>
#include <QKeyEvent>

class ProposalListView: public QListView
{
	Q_OBJECT

	int _nItemsToShow;

public:
	explicit ProposalListView(QWidget *parent = 0);
	QSize sizeHint() const override;

protected:
	bool eventFilter(QObject*, QEvent *event) override;
	Qt::KeyboardModifiers _mods;
signals:
	void completion(QString);
};

#endif // PROPOSALLISTVIEW_H
