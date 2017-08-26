using SmartHomeBackEnd.Models;
using System;
using System.Collections.Concurrent;

namespace SmartHomeBackEnd.Core
{
    public class SwitchNodeMapping
    {
        private static readonly ConcurrentDictionary<Guid, Switch> Mapping = new ConcurrentDictionary<Guid, Switch>();
        static SwitchNodeMapping()
        {
            var switch1 = new Guid("4987B1D7-E272-4C5F-89D9-747140365CEA");
            var switch2 = new Guid("A10A5CB6-CCEF-4A32-8988-B49B25F77C8E");
            var switch3 = new Guid("A859C730-310F-4F0E-815E-4E89E21262BA");
            var switch4 = new Guid("60395B42-C9EF-4A56-A978-4D09A37B0728");
            Mapping.TryAdd(switch1, new Switch
            {
                Id = switch1,
                Node = new Guid("4aef5569966a4de68da2237b68f83f95"),
                Number = 1
            });
            Mapping.TryAdd(switch2, new Switch
            {
                Id = switch2,
                Node = new Guid("4aef5569966a4de68da2237b68f83f95"),
                Number = 2
            });
            Mapping.TryAdd(switch3, new Switch
            {
                Id = switch3,
                Node = new Guid("4aef5569966a4de68da2237b68f83f95"),
                Number = 3
            });
            Mapping.TryAdd(switch4, new Switch
            {
                Id = switch4,
                Node = new Guid("4aef5569966a4de68da2237b68f83f95"),
                Number = 4
            });
        }

        public static Switch Get(Guid switchId)
        {
            Switch s = new Switch();
            Mapping.TryGetValue(switchId, out s);
            return s;
        }
    }
}
