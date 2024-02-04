#ifndef GUI_RECT_H
#define GUI_RECT_H

#include <utility>
#include <iostream>


namespace gui {

    class Pen
    {
    public:
        Pen(int _Style, int _Width, unsigned long _Color) : iStyle(_Style), cWidth(_Width), color(_Color) {}

        int iStyle;
        int cWidth;
        unsigned long color;
    };

    class Rect
    {
    public:
        Rect(int x, int y, int width, int height);
        Rect(const std::pair<int,int> &topLeft, const std::pair<int,int> &size);
        Rect();

        // copy
        Rect(const Rect& other);
        Rect &operator=(Rect& other);

        // move
        Rect(Rect&& other);
        Rect &operator=(Rect&& other);

        friend bool operator==(const Rect& lhs, const Rect& rhs);
        friend std::ostream& operator<<(std::ostream& os, const Rect& obj);
        friend std::istream& operator>>(std::istream& is, Rect& obj);


        bool valid() const;

        // getter's and setter's
        int width() const;
        void setWidth(int width);

        int height() const;
        void setHeight(int height);

        int x() const;
        void setX(int x);

        int y() const;
        void setY(int y);

        int &left();
        int left() const;
        void setLeft(int pos);

        int &top();
        int top() const;
        void setTop(int pos);

        int &right();
        int right() const;
        void setRight(int pos);

        int &bottom();
        int bottom() const;
        void setBottom(int pos);

        std::pair<int,int> topLeft() const;
        void setTopLeft(const std::pair<int,int> &p);

        std::pair<int,int> bottomRight() const;
        void setBottomRight(const std::pair<int,int> &p);

        std::pair<int,int> topRight() const;
        void setTopRight(const std::pair<int,int> &p);

        std::pair<int,int> bottomLeft() const;
        void setBottomLeft(const std::pair<int,int> &p);

        void inflate(int dx, int dy);

        std::pair<int,int> center() const;
        std::pair<int,int> size() const;


        // transform's
        void rotate(double angle);  // TODO add implementation + control

    private:
        // member's
        int mX1, mX2;
        int mY1, mY2;

        void copy(const Rect& r);

    };

    inline bool operator==(const Rect& lhs, const Rect& rhs)
    {
        if (lhs.mX1 != rhs.mX1)
            return false;
        if (lhs.mX2 != rhs.mX2)
            return false;
        if (lhs.mY1 != rhs.mY1)
            return false;
        if (lhs.mY2 != rhs.mY2)
            return false;
        return true;
    }

    inline std::ostream& operator<<(std::ostream& os, const Rect& obj)
    {
        os << obj.mX1 << obj.mX2 << obj.mY1 << obj.mY2;
        return os;
    }

    inline std::istream& operator>>(std::istream& is, Rect& obj)
    {
        is >> obj.mX1 >> obj.mX2 >> obj.mY1 >> obj.mY2;
        return is;
    }

}


#endif // GUI_RECT_H
