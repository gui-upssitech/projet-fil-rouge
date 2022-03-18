package dev.miniteldo.search.model.engines.miniteldoengine;

import java.io.IOException;

public class Test {

    public static void main(String[] args) throws IOException {
        MiniteldoEngine miniteldoEngine = new MiniteldoEngine();
        System.out.println(miniteldoEngine.login("root"));
        miniteldoEngine.changePassword("roote");
        System.out.println(miniteldoEngine.login("roote"));
        System.out.println(miniteldoEngine.login("root"));
        miniteldoEngine.changePassword("root");
        System.out.println(miniteldoEngine.login("root"));
    }
}