package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.TextSearcher;

import java.io.IOException;

public class Test {

    public static void main(String[] args) throws IOException {
        TextSearcher textSearcher = new TextSearcher("search-engine", SearcherType.TEXT_COMPLETION);
        System.out.println(textSearcher.getWordsList());
    }
}