package dev.miniteldo.search.model.engines.miniteldoengine;

import dev.miniteldo.search.model.engines.SearchResult;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.DescriptorFactory;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.DescriptorType;
import dev.miniteldo.search.model.engines.miniteldoengine.descriptorviewer.TextDescriptor;
import dev.miniteldo.search.model.tools.FileTools;

import java.io.IOException;
import java.util.ArrayList;

public class Test {

    public static void main(String[] args) {
        TextDescriptor textDescriptor = (TextDescriptor) DescriptorFactory.getDescriptor("search-engine", DescriptorType.TEXT, "06-US_Open___Mauresmo_et_utf8.xml");
        System.out.println(textDescriptor);
    }
}