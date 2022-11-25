#include "Widget.hpp"

namespace gGUI {
    class DropOutMenu : public Widget {
    protected:
        bool dropped = false;
    public:
        Slot dropOut = Slot(this, SLOT_FUNC(DropOutMenu::handleDropOut));
        Slot pullUp  = Slot(this, SLOT_FUNC(DropOutMenu::handlePullUp));
        Slot toggle  = Slot(this, SLOT_FUNC(DropOutMenu::handleToggle));
        DropOutMenu(size_t in_x, size_t in_y, size_t in_w, size_t in_h, Widget *p, char *name) : Widget(in_x, in_y, in_w, in_h, p, TextureManager::code::buttonbg)
        {
            Button *action = new Button(0, 0, w, h, nullptr, name);
            action->setParent(this);
            children.push_back(action);
            action->clicked.connect(toggle);
        }

        virtual void add_child(Widget *ch) override
        {
            assert(ch != nullptr);
            size_t ch_y;
            if (not children.empty())
                ch_y = children.back()->getY() + children.back()->getHeight();
            else
                ch_y = y;
            children.push_back(ch);
            ch->move(0, ch_y);
            ch->resize(w, -1);
            if (dropped)
                ch->show();
            else
                ch->hide();
        }

        virtual void resize(size_t new_w, size_t new_h) override
        {
            (*children.begin())->resize(new_w, new_h);
            Widget::resize(new_w, new_h);
        }

        void handleToggle(Event ev)
        {
            if (dropped)
                handlePullUp(ev);
            else
                handleDropOut(ev);
        }

        void handleDropOut(Event ev)
        {
            dropped = true;
            for (size_t i = 1; i < children.size(); ++i)
                children[i]->show();
        }

        void handlePullUp(Event ev)
        {
            dropped = false;
            for (size_t i = 1; i < children.size(); ++i)
                children[i]->hide();
        }
    };
}
