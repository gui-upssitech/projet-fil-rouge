package dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurator.loadConfigs;

public class AudioDescriptor extends Descriptor {
    private String fileName;
    private int window_size;
    private int num_windows;
    private int[][] histograms;

    public AudioDescriptor(String miniteldoEnginePath, String fileName) {
        this.fileName = fileName;
        try {
            getAudioDescriptor(miniteldoEnginePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void getAudioDescriptor(String miniteldoEnginePath) throws IOException {
        String line;
        Command command = new Command(miniteldoEnginePath, DescriptorType.AUDIO, fileName);
        BufferedReader reader = command.getResult();

        line = reader.readLine();
        if (line != null) {
            id = line;
        }

        line = reader.readLine();
        line = reader.readLine();
        if (line != null) {
            num_windows = Integer.parseInt(line);
        }

        window_size = loadConfigs(miniteldoEnginePath).get(Configurations.AUDIO_INTERVAL);

        histograms = new int[num_windows][window_size];

        Pattern p = Pattern.compile("(\\d+)");

        for (int i = 0; i < num_windows; i++) {
            line = reader.readLine();
            if (line != null) {
                Matcher m = p.matcher(line);

                for (int j = 0; j < window_size; j++) {
                    m.find();
                    histograms[i][j] = Integer.parseInt(m.group());
                }
            }
        }
    }

    public String getFileName() {
        return fileName;
    }

    public int getWindow_size() {
        return window_size;
    }

    public int getNum_windows() {
        return num_windows;
    }

    public int[][] getHistograms() {
        return histograms;
    }

    @Override
    public String toString() {
        String descriptor_text = "AudioDescriptor{" +
                "fileName='" + fileName + '\'' +
                ", id='" + id + '\'' +
                ", window_size=" + window_size +
                ", num_windows=" + num_windows +
                ", histograms=";
        for (int[] row : histograms) {
            descriptor_text += Arrays.toString(row) + "\n\r";
        }
        descriptor_text += "}";
        return descriptor_text;
    }
}
