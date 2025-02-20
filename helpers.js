function splitWithDots(number, groupSize = 3) {
    let [integer, decimal] = String(number).split('.')
    let num = integer
    const zeroes = (groupSize - (num.length % groupSize)) % groupSize
    num = num.padStart(num.length + zeroes, '0')

    let groupsCnt = num.length / groupSize
    let groups = []
    for (let i = 0; i < groupsCnt; i++) {
        let from = i === 0 ? zeroes : groupSize * i
        let to = (i + 1) * groupSize
        let sub = num.substring(from, to)
        groups.push(sub)
    }

    const suffix = decimal ? '.' + decimal : ''
    return groups.join('.') + suffix
}

function formatMoney(number) {
    const split = String(number.toFixed(2)).split('.')
    let integer = split[0]
    let decimal = split[1]

    return splitWithDots(integer) + ' руб. ' + decimal + ' коп.'
}
