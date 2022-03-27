package dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer;

public enum DescriptorType {
    TEXT("descriptor_view", "text"),
    IMAGE("descriptor_view", "image"),
    AUDIO("descriptor_view", "audio");

    private String commandName;
    private String descriptorType;

    DescriptorType(String commandName, String descriptorType) {
        this.commandName = commandName;
        this.descriptorType = descriptorType;
    }

    public String getCommandName() {
        return commandName;
    }

    public String getDescriptorType() {
        return descriptorType;
    }
}
