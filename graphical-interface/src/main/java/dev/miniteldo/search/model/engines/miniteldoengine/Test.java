package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.searcher.Searcher;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.searcher.SearcherType;
import dev.miniteldo.search.model.tools.Regex;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Test {

    public static void main(String[] args) throws IOException {
        //Searcher searcher = SearcherFactory.getSearcher(SearcherType.TEXT_PATH);
        //System.out.println(searcher.search("data/text/03-Mimer_un_signal_nerveux_pour_utf8.xml"));

        MiniteldoEngine miniteldoEngine = new MiniteldoEngine();
        System.out.println(miniteldoEngine.login("root"));
    }
}