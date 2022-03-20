package dev.miniteldo.search.model.engines.miniteldoengine.admin;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;

public class Configurator {
    public static boolean configure(String miniteldoEnginePath, Configurations configuration, String value) throws IOException {
        boolean result = false;
        String line;
        Command command = new Command(miniteldoEnginePath, configuration, value);

        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }
}
