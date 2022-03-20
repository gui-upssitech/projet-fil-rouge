package dev.miniteldo.search.model.engines.miniteldoengine;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collection;

public class Test {

    public static void main(String[] args) throws IOException {
        MiniteldoEngine miniteldoEngine = new MiniteldoEngine("search-engine");
        ArrayList<String> positive = new ArrayList<>();
        ArrayList<String> negative = new ArrayList<>();
        positive.add("football");
        negative.add("club");

        System.out.println(miniteldoEngine.keywordSearch(positive, negative));
    }
}