package dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer;

public class DescriptorFactory {

    public static Descriptor getDescriptor(String miniteldoEnginePath, DescriptorType descriptorType, String fileName) {

        Descriptor descriptor = null;

         switch(descriptorType) {
            case TEXT:
                descriptor = new TextDescriptor(miniteldoEnginePath, fileName);
                break;

            case IMAGE:
                descriptor = new ImageDescriptor(miniteldoEnginePath, fileName);
                break;

            case AUDIO:
                descriptor = new AudioDescriptor(miniteldoEnginePath, fileName);
                break;
        }

        return descriptor;
    }
}
