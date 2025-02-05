import QtQuick 2.15

import MuseScore.UiComponents 1.0

Item {
    id: root

    property var model: null

    property Component itemDelegate: Item {}
    property string sectionRole: "sectionRole"

    property int cellWidth: 0
    property int cellHeight: 0

    property int rows: 0
    property int rowSpacing: 2
    property int columns: 0
    property int columnSpacing: 2

    width: gridView.columns * gridView.cellWidth - root.columnSpacing
    height: gridView.rows * gridView.cellHeight - root.rowSpacing

    SortFilterProxyModel {
        id: filterModel

        sourceModel: root.model

        filters: [
            FilterValue {
                roleName: root.sectionRole
                roleValue: modelData
                compareType: CompareType.Equal
            }
        ]
    }

    GridView {
        id: gridView

        readonly property int columns: {
            if (root.columns === -1 && root.rows === -1) {
                return gridView.count
            }

            return root.columns !== -1 ? root.columns : Math.ceil(gridView.count / gridView.rows)
        }

        readonly property int rows: {
            if (root.columns === -1 && root.rows === -1) {
                return 1
            }

            return root.rows !== -1 ? root.rows : Math.ceil(gridView.count / gridView.columns)
        }

        anchors.fill: parent
        anchors.leftMargin: -root.columnSpacing / 2
        anchors.rightMargin: anchors.leftMargin
        anchors.topMargin: -root.rowSpacing / 2
        anchors.bottomMargin: anchors.topMargin

        cellWidth: root.cellWidth + root.columnSpacing
        cellHeight: root.cellHeight + root.rowSpacing

        model: filterModel

        interactive: false
        clip: true

        delegate: Item {
            width: gridView.cellWidth
            height: gridView.cellHeight

            Loader {
                width: root.cellWidth
                height: root.cellHeight

                anchors.centerIn: parent

                property var itemModel: null
                sourceComponent: root.itemDelegate

                onLoaded: {
                    itemModel = Qt.binding( function() { return Boolean(model) ? model : null });
                }
            }
        }
    }
}
