package dev.miniteldo.search.model.engines.miniteldoengine.admin;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.HashMap;

public class Configurator {

    private static final String parametersPath = "/admin/parameters.conf";

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

    public static HashMap<Configurations, Integer> loadConfigs(String miniteldoEnginePath) {
        BufferedReader reader;
        HashMap<Configurations, Integer> returnValue = new HashMap<>();

        try {
            reader = new BufferedReader(new FileReader("../" + miniteldoEnginePath + parametersPath));
            String line = reader.readLine();
            while(line != null) {
                if(line.length() > 0 && line.charAt(0) != '#') {
                    String[] splits = line.split("=");
                    Configurations configuration = Configurations.getConfiguration(splits[0]);
                    Integer value = Integer.valueOf(splits[1]);
                    if(configuration != null) {
                        returnValue.put(configuration, value);
                    }
                }

                line = reader.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return returnValue;
    }
}
