package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.Descriptor;

import java.io.IOException;

public class Test {

    public static void main(String[] args) throws IOException {
        MiniteldoEngine miniteldoEngine = new MiniteldoEngine("search-engine");
        System.out.println(miniteldoEngine.hexacodeImageSearch("FF0000"));
    }
}