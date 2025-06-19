function onlyUnique(value, index, array) {
    console.log(value)
  return array.indexOf(value) === index;
}

class Edge {
    constructor(node, destination, weight) {
        return [node, destination, weight]
    }
}

class Graph {
    constructor(pairs) {
        this.pairs = pairs || [[], [], []]
        this.nodes = graph.pairs[0].concat(graph.pairs[1]).filter(onlyUnique)
    }
    addEdge(node, d, w) {
        this.pairs[0].push(node)
        this.pairs[1].push(d)
        this.pairs[2].push(w)
    }
}

let graph = new Graph();
graph.addEdge('A', 'B', 1)
graph.addEdge('A', 'C', 2)
graph.addEdge('B', 'C', 3)
graph.addEdge('C', 'D', 4)
graph.addEdge('D', 'A', 5)

graph.nodes = graph.pairs[0].concat(graph.pairs[1]).filter(onlyUnique)
console.log(graph.pairs)
console.log(t)