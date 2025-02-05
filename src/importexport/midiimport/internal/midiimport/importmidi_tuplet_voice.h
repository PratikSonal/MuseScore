#ifndef IMPORTMIDI_TUPLET_VOICE_H
#define IMPORTMIDI_TUPLET_VOICE_H

#include <vector>
#include <map>
#include <list>

namespace Ms {
class ReducedFraction;
class MidiChord;

namespace MidiTuplet {
struct TupletInfo;

struct TiedTuplet
{
    int tupletId;
    int voice;
    std::pair<const ReducedFraction, MidiChord>* chord;    // chord the tuplet is tied with
    std::vector<int> tiedNoteIndexes;     // indexes of tied notes of that chord
};

int tupletVoiceLimit();

bool excludeExtraVoiceTuplets(
    std::vector<TupletInfo>& tuplets, std::list<std::multimap<ReducedFraction, MidiChord>::iterator>& nonTuplets,
    std::list<TiedTuplet>& backTiedTuplets, const std::multimap<ReducedFraction, MidiChord>& chords, const ReducedFraction& basicQuant,
    const ReducedFraction& barStart, int barIndex);

std::list<TiedTuplet>
findBackTiedTuplets(
    const std::multimap<ReducedFraction, MidiChord>& chords, const std::vector<TupletInfo>& tuplets, const ReducedFraction& prevBarStart,
    const ReducedFraction& startBarTick, const ReducedFraction& basicQuant, int currentBarIndex);

void assignVoices(
    std::vector<TupletInfo>& tuplets, std::list<std::multimap<ReducedFraction, MidiChord>::iterator>& nonTuplets,
    std::list<TiedTuplet>& backTiedTuplets, const std::multimap<ReducedFraction, MidiChord>& chords, const ReducedFraction& basicQuant,
    const ReducedFraction& barStart, int barIndex);

std::pair<ReducedFraction, ReducedFraction>
chordInterval(const std::pair<const ReducedFraction, MidiChord>& chord, const std::multimap<ReducedFraction, MidiChord>& chords,
              const ReducedFraction& basicQuant, const ReducedFraction& barStart);

#ifdef QT_DEBUG

bool haveOverlappingVoices(
    const std::list<std::multimap<ReducedFraction, MidiChord>::iterator>& nonTuplets, const std::vector<TupletInfo>& tuplets,
    const std::list<TiedTuplet>& backTiedTuplets, const std::multimap<ReducedFraction, MidiChord>& chords,
    const ReducedFraction& basicQuant, const ReducedFraction& barStart);

#endif
} // namespace MidiTuplet
} // namespace Ms

#endif // IMPORTMIDI_TUPLET_VOICE_H
