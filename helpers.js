function formatMoney(number) {
    const split = String(number).split('.')
    let integer = split[0]
    let decimal = split[1] ? split[1] : '00'

    decimal = decimal.padEnd(2, '0')

    const zeroes = (3 - (integer.length % 3)) % 3
    integer = integer.padStart(integer.length + zeroes, '0')

    let groupsCnt = integer.length / 3
    let groups = []
    for (let i = 0; i < groupsCnt; i++) {
        let from = i === 0 ? zeroes : 3 * i
        let to = 3 * i + 3
        let sub = integer.substring(from, to)
        groups.push(sub)
    }
    return groups.join('.') + ' руб. ' + decimal + ' коп.'
}
