package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurator;
import java.io.IOException;

public class Test {

    public static void main(String[] args) throws IOException, InterruptedException {
        System.out.println(Configurator.loadConfigs("search-engine"));
        Configurator.configure("search-engine", Configurations.INDEXING_MODE, "0");
        System.out.println(Configurator.loadConfigs("search-engine"));
    }
}