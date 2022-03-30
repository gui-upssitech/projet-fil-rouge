package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.Descriptor;

import java.io.IOException;

public class Test {

    public static void main(String[] args) throws IOException {
        MiniteldoEngine miniteldoEngine = new MiniteldoEngine("search-engine");
        Descriptor descriptor = miniteldoEngine.viewDescriptor("jingle_fi.wav");
        System.out.println(descriptor);
    }
}