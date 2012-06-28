#ifndef _POPUP_H_
#define _POPUP_H_

#include "../cWidget.h"
#include "../cTrigger.h"
#include "../cSpriteObj.h"
#include "../cAnimation.h"
#include "../cApplication.h"

#include <SFML/System/Vector2.hpp>

class Popup : public SpriteObj, public Widget {
public:

	Popup(const char * title, bool autoRemove = true);

	virtual ~Popup();

	virtual void Draw(Application &App);

	virtual void nextFrame();

	virtual void handleEvent(const sf::Input &Input);

private:
    /*
	class Item : public RefCnt {
	public:
		Item() {
            text = NULL;
            texture = NULL;
            x = y = 0;
        }
		Item(const char *ch, Texture * txr): text(strdup(ch)), texture(txr) { x = y = 0; }
		virtual ~Item() {
            if (text)
            free((void *)text);
        }

		char			* text;
		float			x, y;
		RefPtr<Texture>		texture;
	};

	class PopupBirth : public Animation {
	public:
		PopupBirth() { }
		virtual ~PopupBirth() { }

		virtual void nextFrame(SpriteObj *t) {
			Popup * p = (Popup *)t;
			sf::Vector2f vector_temp;

			vector_temp = p->GetScale();

			if (vector_temp < sf::Vector2f(1.0, 1.0)) {
				vector_temp += ((sf::Vector2f(1.0, 1.0) - p->GetScale()) / sf::Vector2f(2.0f, 2.0f));
				p->SetScale(vector_temp);
				if (p->GetScale >= sf::Vector2f(0.99f, 0.99f)) {
					p->SetScale(sf::Vector2f(1.0, 1.0));
				}
			}

			vector_temp = p->GetScale();

			if (vector_temp >= sf::Vector2f(1.0f, 1.0f)) {
				p->m_txtalpha += 1.0f / (hz/4);
				if (p->m_txtalpha >= 1.0f) {
					p->m_txtalpha = 1.0f;
					p->m_anim = NULL;
					complete(t);
				}
			}
		}
	};

	class PopupDeath : public Animation {
	public:
		PopupDeath() { }
		virtual ~PopupDeath() { }

		virtual void nextFrame(SpriteObj *t) {
			Popup * p = (Popup *)t;

			if (p->m_txtalpha > 0.0f) {
				p->m_txtalpha -= 1.0f / (hz/4);
				if (p->m_txtalpha <= 0.0f) {
					p->m_txtalpha = 0.0f;
				}
			}

			if (p->m_txtalpha <= 0.0f) {
				if (p->m_scale > 0.01f) {
					p->m_scale -= p->m_scale / 2.0f;
					if (p->m_scale <= 0.01f) {
						p->m_scale = 0.01f;
						p->m_anim = NULL;
						complete(t);
					}
				}
			}
		}
	};

	class AutoRemove : public Trigger {
	public:
		AutoRemove() { }
		virtual ~AutoRemove() { }

		void trigger(SpriteObj *t, Animation *a) {
			SpriteObj * p = t->getParent();
			if (p) {
				p->subRemove(t);
			}

			Trigger::trigger(t, a);
		}
	};
	*/

};

#endif	/* _POPUP_H */

