//
// Created by cheyulin on 1/19/17.
//

#include <boost/graph/graphviz.hpp>

enum files_e {
    dax_h, yow_h, boz_h, zow_h, foo_cpp,
    foo_o, bar_cpp, bar_o, libfoobar_a,
    zig_cpp, zig_o, zag_cpp, zag_o,
    libzigzag_a, killerapp, N
};

const char *name[] = {"dax.h", "yow.h", "boz.h", "zow.h", "foo.cpp",
                      "foo.o", "bar.cpp", "bar.o", "libfoobar.a",
                      "zig.cpp", "zig.o", "zag.cpp", "zag.o",
                      "libzigzag.a", "killerapp"};

int main(int, char *[]) {
    using Edge= std::pair<int, int>;
    Edge used_by[] = {
            Edge(dax_h, foo_cpp), Edge(dax_h, bar_cpp), Edge(dax_h, yow_h),
            Edge(yow_h, bar_cpp), Edge(yow_h, zag_cpp),
            Edge(boz_h, bar_cpp), Edge(boz_h, zig_cpp), Edge(boz_h, zag_cpp),
            Edge(zow_h, foo_cpp),
            Edge(foo_cpp, foo_o),
            Edge(foo_o, libfoobar_a),
            Edge(bar_cpp, bar_o),
            Edge(bar_o, libfoobar_a),
            Edge(libfoobar_a, libzigzag_a),
            Edge(zig_cpp, zig_o),
            Edge(zig_o, libzigzag_a),
            Edge(zag_cpp, zag_o),
            Edge(zag_o, libzigzag_a),
            Edge(libzigzag_a, killerapp)
    };

    const auto num_edges = sizeof(used_by) / sizeof(Edge);
    int weights[num_edges];
    std::fill(weights, weights + num_edges, 1);

    using namespace boost;
    using Graph= adjacency_list<vecS, vecS, directedS,
            property<vertex_color_t, default_color_type>, property<edge_weight_t, int>>;
    Graph g(used_by, used_by + num_edges, weights, N);
    write_graphviz(std::cout, g, make_label_writer(name));
}