import QtQuick 2.12
import QtQuick.Controls 2.12

SpinBox {
    id: spinbox
    from: 0
    value: 1
    to: 100 * ratio
    stepSize: Math.pow(10, decimals / 2)
    anchors.centerIn: parent

    property int decimals: 2
    property real realValue: value / ratio
    property int ratio: Math.pow(10, decimals)

    validator: DoubleValidator {
        bottom: Math.min(spinbox.from, spinbox.to)
        top:  Math.max(spinbox.from, spinbox.to)
    }

    textFromValue: function(value, locale) {
        return Number(value / ratio).toLocaleString(locale, 'f', spinbox.decimals)
    }

    valueFromText: function(text, locale) {
        return Number.fromLocaleString(locale, text) * ratio
    }
}
