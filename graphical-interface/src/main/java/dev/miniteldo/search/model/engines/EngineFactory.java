package dev.miniteldo.search.model.engines;

import dev.miniteldo.search.model.engines.miniteldoengine.MiniteldoEngine;

/**
 * class: EngineFactory
 * author: Guillaume Roussin
 * date: 16/03/2022
 * <p>
 * This class helps reduce memory usage of the app
 */
public class EngineFactory {

    // Methods
    public static SearchEngine createEngine(Engines engineType) {
        return switch (engineType) {
            case MINITELDO_ENGINE -> new MiniteldoEngine("search-engine");
            case MINITELDO_ENGINE_2 -> new MiniteldoEngine("search-engine-2");
        };
    }
}