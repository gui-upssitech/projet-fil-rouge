package dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer;

import dev.miniteldo.search.model.engines.miniteldoengine.command.Command;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ImageDescriptor extends Descriptor {

    private String fileName;
    private int size;
    private int max = 0;
    private int[] histogram;
    public ImageDescriptor(String miniteldoEnginePath, String fileName) {
        this.fileName = fileName;
        try {
            getImageDescriptor(miniteldoEnginePath);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void getImageDescriptor(String miniteldoEnginePath) throws IOException {

        String line;
        Command command = new Command(miniteldoEnginePath, DescriptorType.IMAGE, fileName);
        BufferedReader reader = command.getResult();

        line = reader.readLine();
        if(line != null) {
            id = line;
        }

        line = reader.readLine();
        line = reader.readLine();
        if(line != null) {
            Pattern p = Pattern.compile("(\\d+)");
            Matcher m = p.matcher(line);
            size = (int) m.results().count();
            histogram = new int[size];

            m = p.matcher(line);
            for(int i = 0; i < size; i++) {
                m.find();
                histogram[i] = Integer.parseInt(m.group());
                if(histogram[i] > max) {
                    max = histogram[i];
                }
            }
        }
    }

    public String getFileName() {
        return fileName;
    }

    public int getSize() {
        return size;
    }

    public int getMax() {
        return max;
    }

    public int[] getHistogram() {
        return histogram;
    }

    @Override
    public String toString() {
        return "ImageDescriptor{" +
                "id='" + id + '\'' +
                ", fileName='" + fileName + '\'' +
                ", size=" + size +
                ", histogram=" + Arrays.toString(histogram) +
                '}';
    }
}
