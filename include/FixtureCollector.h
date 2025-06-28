#pragma once
#include <Box2D/Box2D.h>
#include <unordered_set>


class FixtureCollector : public b2QueryCallback {
public:
    std::unordered_set<b2Fixture*>& fixtures;
    b2Body* selfBody;

    FixtureCollector(std::unordered_set<b2Fixture*>& out, b2Body* self = nullptr)
        : fixtures(out), selfBody(self) {}

    bool ReportFixture(b2Fixture* fixture) override {
        // تجاهل نفسه
        if (fixture->GetBody() == selfBody)
            return true;
        if (fixture->GetType() != b2_dynamicBody)
            return true;

        fixtures.insert(fixture);
        return true; // استمر بالتجميع
    }
};
