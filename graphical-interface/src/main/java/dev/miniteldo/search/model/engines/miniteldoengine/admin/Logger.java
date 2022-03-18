package dev.miniteldo.search.model.engines.miniteldoengine.admin;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;

public class Logger {
    static public boolean login(String password) throws IOException {
        Command command = new Command(LoggerOptions.LOGIN, password);
        BufferedReader reader = command.getResult();
        String line;
        boolean result = false;

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }

    static public boolean resetPassword(String newPassword) throws IOException {
        Command command = new Command(LoggerOptions.NEW_PASSWORD, newPassword);
        BufferedReader reader = command.getResult();
        String line;
        boolean result = false;

        while ((line = reader.readLine()) != null) {
            if (line.equals("1")) {
                result = true;
            }
        }
        return result;
    }
}
