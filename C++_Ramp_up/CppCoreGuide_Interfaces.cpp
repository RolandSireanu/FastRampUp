namespace GPU
{
    void Expects(bool aCondResult)
    {
        assert(aCondResult);
    }

    void Ensures(bool aCondResult)
    {
        Expects(aCondResult);
    }

    struct Point
    {
        int x;
        int y;
    };
    
    //Bad example, make interface precise and strongly typed
    // bool drawLine(int v1, int v2, int v3, int v4)
    bool drawLine(Point upperLeft, Point downRight)
    {
        //Expres preconditions with Expects
        Expects(upperLeft.x >= 0 && upperLeft.y >= 0);
        Expects(downRight.x >= 0 && downRight.y >= 0);

        Ensures(/*Post-conditions, like return should be either true or false*/ true);
        return true;
    }
    
    //Don't pass array as a single pointer, it looses size
    //void drawLines(Point* upperLeftPoints, Point* downRightPoints)
    void drawLines (std::span<Point> upperLeftPoints, span<Point> downRightPoints)
    {    
    }
    
    //Prefer empty abstract classes with no non-static member data
    class GeometricObject
    {
        public:
            virtual int id() const noexcept = 0;
            virtual bool draw() const noexcept = 0;
            // ...
            // ... no data members ...
            // ...
            virtual bool flip() const = 0;
    };

};
