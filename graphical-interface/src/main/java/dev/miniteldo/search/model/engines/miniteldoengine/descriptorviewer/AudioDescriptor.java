package dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer;

import dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurations;
import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.HashMap;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static dev.miniteldo.search.model.engines.miniteldoengine.admin.Configurator.loadConfigs;

public class AudioDescriptor extends Descriptor {

    private final static int Fe = 16000;

    private final String fileName;
    private int histogramIntervals;
    private int windowSize;
    private float duration;
    private int numWindows;
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
            numWindows = Integer.parseInt(line);
        }

        HashMap<Configurations, Integer> configs = loadConfigs(miniteldoEnginePath);
        histogramIntervals = configs.get(Configurations.AUDIO_INTERVAL);
        windowSize = configs.get(Configurations.AUDIO_SAMPLES);
        duration = windowSize * numWindows / (float) Fe;

        histograms = new int[numWindows][histogramIntervals];

        Pattern p = Pattern.compile("(\\d+)");

        for (int i = 0; i < numWindows; i++) {
            line = reader.readLine();
            if (line != null) {
                Matcher m = p.matcher(line);

                for (int j = 0; j < histogramIntervals; j++) {
                    m.find();
                    histograms[i][j] = Integer.parseInt(m.group());
                }
            }
        }
    }

    public int findIdxByTimeCode(float timeCode) throws IllegalArgumentException {
        if(timeCode < 0 || timeCode > duration) {
            throw new IllegalArgumentException("time code is not between 0 and " + String.valueOf(duration) + ".");
        }

        if(windowSize == 0) {
            throw new IllegalArgumentException("Descriptor is not initialized.");
        }

        int idx = (int) (timeCode * Fe / (float) windowSize);
        if(idx < 0) {
            idx = 0;
        } else if(idx >= numWindows) {
            idx = numWindows - 1;
        }

        return idx;
    }

    public String getFileName() {
        return fileName;
    }

    public int getHistogramIntervals() {
        return histogramIntervals;
    }

    public int getNumWindows() {
        return numWindows;
    }

    public int[][] getHistograms() {
        return histograms;
    }

    public int getWindowSize() {
        return windowSize;
    }

    public float getDuration() {
        return duration;
    }

    @Override
    public String toString() {
        String descriptor_text = "AudioDescriptor{" +
                "fileName='" + fileName + '\'' +
                ", id='" + id + '\'' +
                ", histogramIntervals=" + histogramIntervals +
                ", windowSize=" + windowSize +
                ", duration=" + duration +
                ", numWindows=" + numWindows +
                ", histograms=";
        for (int[] row : histograms) {
            descriptor_text += Arrays.toString(row) + "\n\r";
        }
        descriptor_text += "}";
        return descriptor_text;
    }
}
