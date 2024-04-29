#pragma once

class Angle {
    public:
        Angle() = default;
        Angle(float val);
        float val;
        bool is45();
        bool is90();

    private:
        const float ERROR_TOLERANCE = 0.05;
};
