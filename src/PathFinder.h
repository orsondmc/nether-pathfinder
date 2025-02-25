#pragma once

#include <vector>
#include <optional>

#include "Utils.h"
#include "ChunkGeneratorHell.h"
#include "PathNode.h"
#include "ChunkGen.h"

struct Path {
    enum class Type {
        SEGMENT,
        FINISHED
    };

    Type type;
    BlockPos start;
    BlockPos goal; // where the path wants to go, not necessarily where it ends
    std::vector<BlockPos> blocks;
    std::vector<std::unique_ptr<PathNode>> nodes;
    cache_t chunkCache;

    [[nodiscard]] const BlockPos& getEndPos() const {
        // This should basically never be empty
        return !blocks.empty() ? blocks.back() : this->start;
    }
};

extern std::atomic_flag cancelFlag; // a bit of a hack

std::optional<Path> findPath(const BlockPos& start, const BlockPos& goal, const ChunkGeneratorHell& gen, bool fine);

BlockPos findAir(const BlockPos& pos, const ChunkGeneratorHell& gen);