/*
 * MIT Licence
 * Copyright (c) 2022 Corentin Godeau (@Corendos)
 * More details a https://github.com/Corendos/Reborn
 */

#ifndef REBORN_CHARACTERS_H
#define REBORN_CHARACTERS_H

inline bool is_alpha(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

inline bool is_numeric(char c) { return c >= '0' && c <= '9'; }

inline bool is_alphanumeric(char c) { return is_alpha(c) || is_numeric(c); }

inline bool is_hexadecimal(char c) { return is_numeric(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'); }

inline bool is_space(char c) { return c == ' ' || (c >= '\t' && c <= '\r'); }

#endif // REBORN_CHARACTERS_H
