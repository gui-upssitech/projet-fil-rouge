package dev.miniteldo.search.model.engines.miniteldoengine;

public class Test {

    public static void main(String[] args) {
        MiniteldoEngine miniteldoEngine = new MiniteldoEngine("search-engine");
        System.out.println(miniteldoEngine.viewDescriptor("/home/rxc3445a/Documents/projet-fil-rouge/data/text/06-US_Open___Mauresmo_et_utf8.xml"));
    }
}