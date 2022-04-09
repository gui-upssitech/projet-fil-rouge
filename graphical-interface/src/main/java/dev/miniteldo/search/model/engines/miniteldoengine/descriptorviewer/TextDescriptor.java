package dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.HashMap;

public class TextDescriptor extends Descriptor {
    private String keywordsSize;
    private String wordsSize;
    private HashMap<String, String> dataDescriptor;
    private String fileName;

    public TextDescriptor(String miniteldoEnginePath, String fileName) {
        this.fileName = fileName;
        dataDescriptor = new HashMap<>();
        try {
            getTextDescriptor(miniteldoEnginePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void getTextDescriptor(String miniteldoEnginePath) throws IOException {
        String[] numbers = new String[3];
        int idx = 0;
        String regexData = "\\w+\\s\\d";
        String regexNumber = "\\d+";
        String line;
        Command command = new Command(miniteldoEnginePath, DescriptorType.TEXT, fileName);
        BufferedReader reader = command.getResult();

        while ((line = reader.readLine()) != null) {
            if (line.matches(regexData)) {
                String[] splits = line.split(" ");
                dataDescriptor.put(splits[0], splits[1]);
            } else if (line.matches(regexNumber)) {
                numbers[idx] = line;
                idx++;
            }
        }
        id = numbers[0];
        keywordsSize = numbers[1];
        wordsSize = numbers[2];
    }

    public String getKeywordsSize() {
        return keywordsSize;
    }

    public String getWordsSize() {
        return wordsSize;
    }

    public HashMap<String, String> getDataDescriptor() {
        return dataDescriptor;
    }

    public String getFileName() {
        return fileName;
    }

    @Override
    public String toString() {
        return "TextDescriptor{" +
                "id=" + id +
                ", keywordsSize=" + keywordsSize +
                ", wordsSize=" + wordsSize +
                ", dataDescriptor=" + dataDescriptor +
                ", fileName='" + fileName + '\'' +
                '}';
    }
}