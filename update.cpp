/* update.cpp
 *
 * Copyright (c) 2011, 2012 Chantilly Robotics <chantilly612@gmail.com>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/*
 * Implement registry.  This is really easy.
 */
 
#include <algorithm>
#include "update.h"

void update_registry::register_func(update_registry::update_func f, void * a) {
    update_registry::registry_entry e(f, a);
    if (find_entry(e) == registry.end()) {
        registry.push_back(registry_entry(f, a));
    }
}

void update_registry::unregister_func(update_registry::update_func f, void * a) {
    update_registry::registry_entry e(f, a);
    std::vector<update_registry::registry_entry>::iterator i = find_entry(e);
    if (i != registry.end()) {
        registry.erase(i);
    }
}

void update_registry::update() {
    unsigned upper = registry.size();
    for (unsigned i = 0; i < upper; ++i) {
        registry[i]();
    }
}

std::vector<update_registry::registry_entry>::iterator
update_registry::find_entry(const update_registry::registry_entry& e) {
    return std::find(registry.begin(), registry.end(), e);
}